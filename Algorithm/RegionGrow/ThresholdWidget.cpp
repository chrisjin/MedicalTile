#include"ThresholdWidget.h"
#include"amyMaskLing.h"
#include"amyCanvas.h"
#include"amyUtil.h"
#include<QVBoxLayout>
#include"itkImageRegionIterator.h"
#include<QScrollBar>
#include<QHboxLayout>
#include<QPushButton>
WDialog::WDialog(QWidget*p):QDialog(p)
{
	QVBoxLayout* l=new QVBoxLayout(this);
	m_W=new ThresholdWidget(this);
	l->addWidget(m_W);
	this->resize(512,550);
	QHBoxLayout* hl=new QHBoxLayout(this);
	l->addLayout(hl);
	QPushButton* btn1=new QPushButton("Confirm",this);
	QPushButton* btn2=new QPushButton("Cancel",this);
	hl->addWidget(btn1);
	hl->addWidget(btn2);
	connect(btn1,SIGNAL(clicked()),this,SLOT(accept()));
	connect(btn2,SIGNAL(clicked()),this,SLOT(reject()));
	connect(this,SIGNAL(accepted()),m_W,SLOT(Confirm()));
}
ThresholdWidget::ThresholdWidget(QWidget*p):QWidget(p)
{
	m_Canvas=new amyCanvas;
	m_MaskLing=new amyMaskLing(m_Canvas);
	m_MaskLing->SetInput(0);
	this->resize(512,550);


	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	l->addWidget(m_Canvas);


}
void ThresholdWidget::InitInput()
{
	amyCube::Keeper k=this->GetInput();
	if(!k.IsNull())
	{
		m_Mask=amyCube::New();
		m_Mask->obj=amyCube::tCube::New();
		m_Mask->obj->SetRegions(k->obj->GetLargestPossibleRegion());
		m_Mask->obj->SetSpacing(k->obj->GetSpacing());
		m_Mask->obj->Allocate();
		amyUtil::GetCubeMinMax(k.GetPointer(),m_MaskLing->GetSlice(),m_Min,m_Max);

		m_AboveSlider = new QScrollBar(Qt::Horizontal, this);
		m_AboveSlider->setRange(m_Min-1, m_Max+1);
		m_AboveSlider->setPageStep(20);
		m_AboveSlider->setSingleStep(1);
		m_AboveSlider->setValue((m_Min+m_Max)/2);

		m_BelowSlider = new QScrollBar(Qt::Horizontal, this);
		m_BelowSlider->setRange(m_Min-1, m_Max+1);
		m_BelowSlider->setPageStep(20);
		m_BelowSlider->setSingleStep(1);
		m_BelowSlider->setValue(m_Max);
		m_ThresholdAbove=(m_Min+m_Max)/2;
		m_ThresholdBelow=m_Max;
		connect(m_AboveSlider,SIGNAL(valueChanged(int)),this,SLOT(UpdateAbove(int)));
		connect(m_BelowSlider,SIGNAL(valueChanged(int)),this,SLOT(UpdateBelow(int)));
		connect(m_MaskLing,SIGNAL(s_slicechanging(int)),this,SLOT(UpdateSlice(int)));
		
		this->layout()->addWidget(m_AboveSlider);
		this->layout()->addWidget(m_BelowSlider);
		m_MaskLing->SetTransparency(100);
		
		m_MaskLing->SetMask(m_Mask.GetPointer());
		m_MaskLing->SetInput(k.GetPointer());

		UpdateMask((m_Min+m_Max)/2,m_Max);
		m_MaskLing->UpdateMaskImage();
		//m_MaskLing->Update();
		this->resize(512,550);
		repaint();
	}
}
void ThresholdWidget::UpdateSlice(int slice)
{
	amyCube::Keeper cube=this->GetInput();
	if(cube.IsNull())
	{
		return;
	}
	amyUtil::GetCubeMinMax(cube.GetPointer(),slice,m_Min,m_Max);
	if(m_AboveSlider->value()<m_Min)
		m_AboveSlider->setValue(m_Min);
	if(m_AboveSlider->value()>m_Max)
		m_AboveSlider->setValue(m_Max);
	m_AboveSlider->setRange(m_Min-1, m_Max+1);

	if(m_BelowSlider->value()<m_Min)
		m_BelowSlider->setValue(m_Min);
	if(m_BelowSlider->value()>m_Max)
		m_BelowSlider->setValue(m_Max);
	m_BelowSlider->setRange(m_Min-1, m_Max+1);

	m_Slice=slice;
	UpdateMask(m_ThresholdAbove,m_ThresholdBelow);
}
void ThresholdWidget::UpdateMask(int above,int below)
{
	amyCube::Keeper cube=this->GetInput();
	if(cube.IsNull())
	{
		return;
	}	
	//if(above<=m_Min)
	//	above=m_Min;
	//if(above>=m_Max)
	//	above=m_Max;
	//if(below<=m_Min)
	//	below=m_Min;
	//if(below>=m_Max)
	//	below=m_Max;
	m_ThresholdAbove=above;
	m_ThresholdBelow=below;
	amyCube::tCube::RegionType reg=m_Mask->obj->GetLargestPossibleRegion();
	amyCube::tCube::IndexType  ind=reg.GetIndex();
	amyCube::tCube::SizeType   siz=reg.GetSize();
	ind[2]=m_MaskLing->GetSlice();
	siz[2]=1;
	reg.SetSize(siz);
	reg.SetIndex(ind);
	typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;
	ItrType Itrmask(m_Mask->obj,reg);
	ItrType Itrcube(cube->obj,reg);
	for(Itrmask.GoToBegin(),Itrcube.GoToBegin();
		!Itrmask.IsAtEnd()&&!Itrcube.IsAtEnd();
		++Itrmask,++Itrcube)
	{
		short v=Itrcube.Get();
		if(v>above&&v<below)
			Itrmask.Set(400);
		else
			Itrmask.Set(-400);

	}
	m_MaskLing->UpdateMaskImage();
	m_Canvas->repaint();
}

void ThresholdWidget::UpdateAbove(int v)
{
	m_ThresholdAbove=v;
	UpdateMask(m_ThresholdAbove,m_ThresholdBelow);
}

void ThresholdWidget::UpdateBelow(int v)
{
	m_ThresholdBelow=v;
	UpdateMask(m_ThresholdAbove,m_ThresholdBelow);
}


void ThresholdWidget::Confirm()
{
	amyCube::Keeper cube=this->GetInput();
	if(cube.IsNull())
	{
		return;
	}	
	typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;
	ItrType Itrmask(m_Mask->obj,m_Mask->obj->GetLargestPossibleRegion());
	ItrType Itrcube(cube->obj,cube->obj->GetLargestPossibleRegion());
	for(Itrmask.GoToBegin(),Itrcube.GoToBegin();
		!Itrmask.IsAtEnd()&&!Itrcube.IsAtEnd();
		++Itrmask,++Itrcube)
	{
		short v=Itrcube.Get();
		if(v>m_ThresholdAbove&&v<m_ThresholdBelow)
			Itrmask.Set(400);
		else
			Itrmask.Set(-400);

	}
	int c=0,w=0;
	amyUtil::GetWindowCenterWidth(m_Mask.GetPointer(),c,w);
	m_Mask->windowcenter=c;
	m_Mask->windowwidth=w;
}