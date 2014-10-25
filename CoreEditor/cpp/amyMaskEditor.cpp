#include "amyMaskEditor.h"
#include<QHboxLayout>
#include"amyMaskLing.h"
#include"amyCube.h"
#include<QScrollBar>
#include<QGridLayout>
#include<qpushbutton>
#include<QFormLayout>
#include"amyUtil.h"
#include"itkImageRegionIterator.h"
#include"itkBinaryThresholdImageFunction.h"
#include"itkFloodFilledImageFunctionConditionalIterator.h"
#include"itkImageRegionIteratorWithIndex.h"
#include<QApplication>
#include<QLabel>
#include<QHeaderView>
#include<QIcon>
amyMaskWidget::amyMaskWidget(QWidget *parent)
	: QWidget(parent) 
{
	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	m_Canvas=new amyCanvas(this);
	this->layout()->addWidget(m_Canvas);
	m_MaskLing=new amyMaskLing(m_Canvas);
	m_MaskLing->SetInput(0);
	m_MaskLing->SetCtrlLock(0);
	
	QHBoxLayout* hl=new QHBoxLayout(this);
	l->addLayout(hl);

	QLabel* label=new QLabel(QString::fromLocal8Bit("透明度"),this);
	hl->addWidget(label,1);

	m_TanspSlider = new QScrollBar(Qt::Horizontal, this);
	m_TanspSlider->setRange(0, 255);
	m_TanspSlider->setPageStep(20);
	m_TanspSlider->setSingleStep(1);
	m_TanspSlider->setValue(100);
	hl->addWidget(m_TanspSlider,3);
	connect(m_TanspSlider,SIGNAL(valueChanged(int)),this,
            SLOT(SetTransp(int)));

	this->setToolTip(QString::fromLocal8Bit("按住CTRL拖动鼠标切换断层"));

}       
void amyMaskWidget::SetTransp(int a)
{
	m_MaskLing->SetTransparency(a);
	m_MaskLing->Update();
}
void amyMaskWidget::mouseMoveEvent(QMouseEvent * event)
{

}
EraseChoosePanel::EraseChoosePanel(QWidget* parent):QListWidget(parent)
{
	//this->verticalHeader()->hide();
	//this->horizontalHeader()->hide();
	QPixmap small=QPixmap(5,5);
	small.fill(Qt::black);
	QPixmap mid=QPixmap(10,10);
	mid.fill(Qt::black);
	QPixmap big=QPixmap(25,25);
	big.fill(Qt::black);
	QListWidgetItem* i1=new QListWidgetItem(QIcon(small),"");
	QListWidgetItem* i2=new QListWidgetItem(QIcon(mid),"");
	QListWidgetItem* i3=new QListWidgetItem(QIcon(big),"");

	//this->setRowCount(3);
	//this->setColumnCount(1);
	this->addItem(i1);
	this->addItem(i2);
	this->addItem(i3);
	this->setFixedHeight(65);
	this->setFixedWidth(35);
	//this->set
}
ToolPanel::ToolPanel(QWidget *parent):QWidget(parent)
{
	
	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	
	QPushButton* noedit=new QPushButton(QString::fromLocal8Bit("浏览"),this);
	l->addWidget(noedit);
	connect(noedit,SIGNAL(clicked()),this,SIGNAL(s_noedit()));
	
	QPushButton* eraser=new QPushButton(QString::fromLocal8Bit("橡皮"),this);
	l->addWidget(eraser);
	connect(eraser,SIGNAL(clicked()),this,SIGNAL(s_erase()));

	QPushButton* draw=new QPushButton(QString::fromLocal8Bit("画笔"),this);
	l->addWidget(draw);
	connect(draw,SIGNAL(clicked()),this,SIGNAL(s_draw()));

	EraseChoosePanel* sizech=new EraseChoosePanel(this);
	l->addWidget(sizech);
	connect(sizech,SIGNAL(currentRowChanged(int)),this,SIGNAL(s_erasesize(int)));

	QPushButton* grow=new QPushButton(QString::fromLocal8Bit("区域生长\n(全局)"),this);
	l->addWidget(grow);
	connect(grow,SIGNAL(clicked()),this,SIGNAL(s_grow()));

	QPushButton* growslice=new QPushButton(QString::fromLocal8Bit("区域生长\n(单层)"),this);
	l->addWidget(growslice);
	connect(growslice,SIGNAL(clicked()),this,SIGNAL(s_growinslice()));

	QPushButton* removeotherslice=new QPushButton(QString::fromLocal8Bit("去掉\n其他层"),this);
	l->addWidget(removeotherslice);
	connect(removeotherslice,SIGNAL(clicked()),this,SIGNAL(s_removeothers()));

	QPushButton* removethisslice=new QPushButton(QString::fromLocal8Bit("去掉\n该层"),this);
	l->addWidget(removethisslice);
	connect(removethisslice,SIGNAL(clicked()),this,SIGNAL(s_removethis()));

	l->addStretch(1);
	this->setFixedWidth(70);

}
amyMaskEditor::amyMaskEditor(QWidget *parent)
	: amyVariableEditor(parent)
{
	m_MainWidget=new amyMaskWidget(this);
	this->SetMode(EDIT_NOEDIT);
	QHBoxLayout* l=new QHBoxLayout(this);
	this->GetMainWidget()->setLayout(l);
	ToolPanel* p=new ToolPanel(this);
	l->addWidget(p);
	l->addWidget(m_MainWidget);
	connect(p,SIGNAL(s_grow()),this,SLOT(SetGrow()));
	connect(p,SIGNAL(s_erase()),this,SLOT(SetErase()));
	connect(p,SIGNAL(s_draw()),this,SLOT(SetDraw()));
	connect(p,SIGNAL(s_growinslice()),this,SLOT(SetGrowInSlice()));
	connect(p,SIGNAL(s_removeothers()),this,SLOT(RemoveOtherSlice()));
	connect(p,SIGNAL(s_noedit()),this,SLOT(SetNoEdit()));
	connect(p,SIGNAL(s_removethis()),this,SLOT(RemoveThisSlice()));
	connect(p,SIGNAL(s_erasesize(int)),this,SLOT(SetEraseSize(int)));
	m_MainWidget->m_Canvas->installEventFilter(this);
	//this->setCursor(QCursor::)

	m_EraseSize=5;
}
void amyMaskEditor::SetMode(eMode m)
{
	m_Mode=m;
	m_MainWidget->m_Canvas->setFocus();
}
void amyMaskEditor::SetGrow()
{
	SetMode(EDIT_GROW);
	m_MainWidget->m_MaskLing->SetCtrlLock(1);
	m_MainWidget->m_MaskLing->GetCanvas()->setCursor(Qt::CrossCursor);
}
void amyMaskEditor::SetErase()
{
	SetMode(EDIT_ERASE);
	m_MainWidget->m_MaskLing->SetCtrlLock(1);
	QPixmap  pix(":/CURSOR/Eraser");
	m_MainWidget->m_MaskLing->GetCanvas()->setCursor(QCursor(QCursor(pix.scaled(24,24),0,24)));
}
void amyMaskEditor::SetEraseSize(int a)
{
	if(a==0||a==1||a==2)
	m_EraseSize=(a+1)*3-1;
}
void amyMaskEditor::SetDraw()
{
	SetMode(EDIT_DRAW);
	m_MainWidget->m_MaskLing->SetCtrlLock(1);
	QPixmap  pix(":/CURSOR/Pen");
	m_MainWidget->m_MaskLing->GetCanvas()->setCursor(QCursor(pix.scaled(24,24),24,24));
}
void amyMaskEditor::SetGrowInSlice()
{
	SetMode(EDIT_GROWINSLICE);
	m_MainWidget->m_MaskLing->SetCtrlLock(1);
	m_MainWidget->m_MaskLing->GetCanvas()->setCursor(Qt::CrossCursor);
}
void amyMaskEditor::SetNoEdit()
{
	SetMode(EDIT_NOEDIT);
	m_MainWidget->m_MaskLing->SetCtrlLock(0);
	m_MainWidget->m_MaskLing->GetCanvas()->setCursor(Qt::ArrowCursor);
}
void amyMaskEditor::InitInput()
{
	vector<amyVariable>& vararr=this->GetInputArr();
	//amyVariable v=this->GetInput();
	if(vararr.size()==2)
	{
		//amyCube* cube=v.Get();
		//amyMask::Keeper m=v.Get<amyMask>();
		m_InnerMask=new amyCube;
		m_InnerMask->Copy(vararr[1].Get<amyCube>().GetPointer());
		m_MainWidget->m_MaskLing->SetMask(m_InnerMask);
		m_MainWidget->m_MaskLing->SetInput(vararr[0].Get<amyCube>().GetPointer());

		this->SetMode(EDIT_NOEDIT);
		m_MainWidget->m_MaskLing->SetCtrlLock(0);
		this->resize(600,600);
	}
	else
		return ;
	repaint();
	amyVariableEditor::InitInput();
}
void amyMaskEditor::Confirm()
{
	//amyVariable v=this->GetInput();
	vector<amyVariable>& vararr=this->GetInputArr();
	amyCube::Keeper m=vararr[1].Get<amyCube>();
	m->Copy(m_InnerMask);
	amyVariableEditor::Confirm();
}
amyMaskEditor::~amyMaskEditor()
{
	delete m_InnerMask;
}
bool amyMaskEditor::eventFilter(QObject *target, QEvent *event)
{
	if(target==m_MainWidget->m_Canvas)
	{
		if(event->type()==QEvent::MouseMove)
		{
			mouseCanvasMoveEvent(static_cast<QMouseEvent*>(event));
		}
		if(event->type()==QEvent::MouseButtonPress)
		{
			mouseCanvasPressEvent(static_cast<QMouseEvent*>(event));
		}
	}
	return amyVariableEditor::eventFilter(target,event);
}
void amyMaskEditor::mouseCanvasPressEvent(QMouseEvent * event)
{
	if(QApplication::keyboardModifiers () == Qt::ControlModifier)
		return;
	if(event->buttons()&Qt::LeftButton)
	{
		switch(m_Mode)
		{
		case EDIT_GROW:
			DoGrow(event);
			break;
		case EDIT_GROWINSLICE:
			DoGrowInSlice(event);
			break;
		}
	}
}
void amyMaskEditor::mouseCanvasMoveEvent(QMouseEvent * event)
{
	if(QApplication::keyboardModifiers () == Qt::ControlModifier)
		return;
	if(event->buttons()&Qt::LeftButton)
	{
		switch(m_Mode)
		{
		case EDIT_ERASE:
			DoEraseOrDraw(event,1);
			break;
		case EDIT_DRAW:
			DoEraseOrDraw(event,0);
			break;
		}
	}
}

void amyMaskEditor::DoEraseOrDraw(QMouseEvent * event,bool iserase)
{
	amyCube* mask=m_MainWidget->m_MaskLing->GetMask();
	QPoint p=m_MainWidget->m_MaskLing->MapScreen2Cube(QPoint(event->x(),event->y()));

	amyCube::tCube::IndexType index;
	index[0]=p.x()-(m_EraseSize-1)/2;
	index[1]=p.y()-(m_EraseSize-1)/2;
	index[2]=m_MainWidget->m_MaskLing->GetSlice();
	amyCube::tCube::SizeType size;
	size[0]=m_EraseSize;
	size[1]=m_EraseSize;
	size[2]=1;
	amyCube::tCube::RegionType mregion;
	mregion.SetIndex(index);
	mregion.SetSize(size);

	amyCube::tCube::RegionType lregion=mask->obj->GetLargestPossibleRegion();
	
	if(!lregion.IsInside(mregion))
		return;
	typedef itk::ImageRegionIterator<amyCube::tCube> ItType;
	ItType itr(mask->obj,mregion);
	int v=iserase?-400:400;
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		itr.Set(v);
	}
	m_MainWidget->m_MaskLing->UpdateMaskImage();
	m_MainWidget->m_MaskLing->GetCanvas()->repaint();
}
void amyMaskEditor::Grow3D(int x,int y)
{
	amyCube* mask=m_MainWidget->m_MaskLing->GetMask();
	QPoint p=m_MainWidget->m_MaskLing->MapScreen2Cube(QPoint(x,y));

	amyCube::tCube::IndexType in;
	in[0]=p.x();
	in[1]=p.y();
	in[2]=m_MainWidget->m_MaskLing->GetSlice();
	typedef itk::BinaryThresholdImageFunction< amyCube::tCube, double > FunctionType;
	FunctionType::Pointer function = FunctionType::New();
	function->SetInputImage(mask->obj);
	amyCube::tCube::PixelType pv=mask->obj->GetPixel(in);
	function->ThresholdBetween (pv-10,pv+10);
	typedef itk::FloodFilledImageFunctionConditionalIterator< amyCube::tCube, FunctionType > IteratorType;

	itk::Index<3> seed;
	seed[0] =  p.x();
	seed[1] = p.y();
	seed[2]=  m_MainWidget->m_MaskLing->GetSlice();
	std::vector<itk::Index<3> > seeds;
	seeds.push_back(seed);

	IteratorType it (mask->obj, function, seeds);
	it.GoToBegin();

	while ( !it.IsAtEnd() )
	{
		amyCube::tCube::IndexType index=it.GetIndex();
		it.Set(10000);
		++it;
	}

	amyCube::tCube::RegionType fzregion=mask->obj->GetLargestPossibleRegion();
	typedef itk::ImageRegionIterator<amyCube::tCube> RItrType;
	RItrType itr(mask->obj,fzregion);
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		if(itr.Get()==10000)
		{
			itr.Set(400);
		}
		else
		{
			itr.Set(-400);
		}
	}
}
void amyMaskEditor::Grow2D(int x,int y)
{
	amyCube* mask=m_MainWidget->m_MaskLing->GetMask();
	QPoint p=m_MainWidget->m_MaskLing->MapScreen2Cube(QPoint(x,y));

	amyCube::tCube::RegionType largestregion=mask->obj->GetLargestPossibleRegion();
	typedef itk::Image<short,2> ImageType;
	typedef itk::ImageRegionIterator<amyCube::tCube> RCubeItrType;
	typedef itk::ImageRegionIterator<ImageType>       RImageItrType;
	/////空图像
	ImageType::Pointer ImageToGrow=ImageType::New();
	ImageType::SizeType imsize;
	imsize[0]=largestregion.GetSize()[0];
	imsize[1]=largestregion.GetSize()[1];
	ImageType::IndexType imindex;
	imindex[0]=largestregion.GetIndex()[0];
	imindex[1]=largestregion.GetIndex()[1];
	ImageType::RegionType imregion;
	imregion.SetSize(imsize);
	imregion.SetIndex(imindex);
	ImageToGrow->SetRegions(imregion);
	ImageToGrow->Allocate();
	//////取当前层
	amyCube::tCube::RegionType regiontoslice;
	amyCube::tCube::IndexType  indextoslice=largestregion.GetIndex();
	indextoslice[2]=m_MainWidget->m_MaskLing->GetSlice();
	amyCube::tCube::SizeType   sizetoslice=largestregion.GetSize();
	sizetoslice[2]=1;
	regiontoslice.SetIndex(indextoslice);
	regiontoslice.SetSize(sizetoslice);

	RCubeItrType itrtoslice(mask->obj,regiontoslice);
	RImageItrType itrcopy(ImageToGrow,imregion);
	for(itrtoslice.GoToBegin(),itrcopy.GoToBegin();
		!itrtoslice.IsAtEnd()&&!itrcopy.IsAtEnd();
		++itrtoslice,++itrcopy)
	{
		itrcopy.Set(itrtoslice.Get());
	}
	/////生长条件
	ImageType::IndexType index;
	index[0]=p.x();
	index[1]=p.y();
	typedef itk::BinaryThresholdImageFunction<ImageType, double > FunctionType;
	FunctionType::Pointer function = FunctionType::New();
	function->SetInputImage(ImageToGrow);
	ImageType::PixelType pv=ImageToGrow->GetPixel(index);
	function->ThresholdBetween (pv-10,pv+10); // we are looking to capture 255
	typedef itk::FloodFilledImageFunctionConditionalIterator<ImageType, FunctionType > IteratorType;

	itk::Index<2> seed;
	seed[0] =  p.x();
	seed[1] = p.y();
	//seed[2]=  m_MainWidget->m_MaskLing->GetSlice();
	std::vector<itk::Index<2> > seeds;
	seeds.push_back(seed);

	IteratorType it (ImageToGrow, function, seeds);
	it.GoToBegin();

	while ( !it.IsAtEnd() )
	{
		ImageType::IndexType index=it.GetIndex();
		amyCube::tCube::IndexType cubeindex;
		cubeindex[0]=index[0];
		cubeindex[1]=index[1];
		cubeindex[2]=m_MainWidget->m_MaskLing->GetSlice();
		mask->obj->SetPixel(cubeindex,10000);
		++it;
	}

	
	RCubeItrType itr(mask->obj,regiontoslice);
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		if(itr.Get()==10000)
		{
			itr.Set(400);
		}
		else
		{
			itr.Set(-400);
		}
	}
}
void amyMaskEditor::DoGrow(QMouseEvent * event)
{
	Grow3D(event->x(),event->y());
	m_MainWidget->m_MaskLing->UpdateMaskImage();
	m_MainWidget->repaint();
	m_MainWidget->m_MaskLing->GetCanvas()->repaint();
}
void amyMaskEditor::DoGrowInSlice(QMouseEvent * event)
{
	Grow2D(event->x(),event->y());
	m_MainWidget->m_MaskLing->UpdateMaskImage();
	m_MainWidget->m_MaskLing->GetCanvas()->repaint();
}

void amyMaskEditor::RemoveOtherSlice()
{
	m_MainWidget->m_Canvas->setFocus();
	amyCube* mask=m_MainWidget->m_MaskLing->GetMask();
	amyCube::tCube::RegionType largestregion=mask->obj->GetLargestPossibleRegion();
	
	amyCube::tCube::RegionType regiontoslice;
	amyCube::tCube::IndexType  indextoslice=largestregion.GetIndex();
	indextoslice[2]=m_MainWidget->m_MaskLing->GetSlice();
	amyCube::tCube::SizeType   sizetoslice=largestregion.GetSize();
	sizetoslice[2]=1;
	regiontoslice.SetSize(sizetoslice);
	regiontoslice.SetIndex(indextoslice);
	typedef itk::ImageRegionIteratorWithIndex<amyCube::tCube> RCubeItrType;
	RCubeItrType Itr(mask->obj,largestregion);
	for(Itr.GoToBegin();!Itr.IsAtEnd();++Itr)
	{
		if(regiontoslice.IsInside(Itr.GetIndex()))
		{
			//Itr.Set(400);
		}
		else
		{
			Itr.Set(-400);
		}

	}
	m_MainWidget->m_MaskLing->UpdateMaskImage();
	m_MainWidget->m_MaskLing->GetCanvas()->repaint();
}

void amyMaskEditor::RemoveThisSlice()
{
	m_MainWidget->m_Canvas->setFocus();
	amyCube* mask=m_MainWidget->m_MaskLing->GetMask();
	amyCube::tCube::RegionType largestregion=mask->obj->GetLargestPossibleRegion();

	amyCube::tCube::RegionType regiontoslice;
	amyCube::tCube::IndexType  indextoslice=largestregion.GetIndex();
	indextoslice[2]=m_MainWidget->m_MaskLing->GetSlice();
	amyCube::tCube::SizeType   sizetoslice=largestregion.GetSize();
	sizetoslice[2]=1;
	regiontoslice.SetSize(sizetoslice);
	regiontoslice.SetIndex(indextoslice);
	typedef itk::ImageRegionIteratorWithIndex<amyCube::tCube> RCubeItrType;
	RCubeItrType Itr(mask->obj,regiontoslice);
	for(Itr.GoToBegin();!Itr.IsAtEnd();++Itr)
	{
		Itr.Set(-400);
	}
	m_MainWidget->m_MaskLing->UpdateMaskImage();
	m_MainWidget->m_MaskLing->GetCanvas()->repaint();
}


QIcon amyMaskEditorHive::GetIcon()
{
	QIcon i=QIcon(":/ICON/Folder");
	return i;
}