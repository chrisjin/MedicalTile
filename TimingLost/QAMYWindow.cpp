#include "QAMYWindow.h"
#include<qtoolbutton>
#include<QHBoxLayout>
#include"amyPatientModel.h"
#include<qfiledialog>
#include<QPushButton>
#include<windows.h>
#include"amyDICOMFolder.h"
#include"amyCanvas.h"
#include"amyCubeLing.h"
#include"amyCube.h"
#include"amyDICOM.h"
//#include"QAMYVariableView.h"
#include"amyVariableManager.h"
#include"amyDICOMCanvas.h"
#include<QAction>
#include<QGridLayout>
#include<QSettings>
#include"amyMeasureLing.h"
#include"amyGrid2DViewer.h"
#include<QHBoxLayout>
#include<QStackedWidget>
#include"amyMPRViewer.h"
QAMYWindow::QAMYWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->resize(800,600);
	setAcceptDrops(true);
	this->setWindowTitle("Browser");

	ui.mainToolBar->setIconSize(QSize(30,30));
	ui.mainToolBar->setMovable(0);
	ui.mainToolBar->setFloatable(0);
	this->setAnimated(0);
	ui.mainToolBar->setStyleSheet("background-color:rgb(189,199,216)");
	//QPalette mp=ui.mainToolBar->palette();
	//mp.setColor(QPalette::Window,QColor(47,65,95));
	//ui.mainToolBar->setPalette(mp);
	///打开文件夹
	m_FolderOpenButton=new QToolButton(this);
	m_FolderOpenButton->setIcon(QIcon(":/ICON/Folder"));
	//m_FolderOpenButton->setIconSize(QSize(64,64));
	connect(m_FolderOpenButton,SIGNAL(clicked()),this,SLOT(OpenFolder()));
	ui.mainToolBar->addWidget(m_FolderOpenButton);

	///////2D显示
	m_ViewerContainer=new QStackedWidget(this);
	m_2DViewer=new amyGrid2DViewer(this);
	m_MPRViewer=new amyMPRViewer(this);
	m_ViewerContainer->insertWidget(0,m_2DViewer);
	m_ViewerContainer->insertWidget(1,m_MPRViewer);
	
	///布局菜单
	m_CanvasLayoutButton=new QToolButton(this);
	QMenu *menu=new QMenu(this);
	QAction* Action1x1=new QAction("1 X 1",this);
	menu->addAction(Action1x1);
	connect(Action1x1,SIGNAL(triggered()),this,SLOT(Set2D()));
	connect(Action1x1,SIGNAL(triggered()),m_2DViewer,SLOT(Set1X1()));
	QAction* Action2x2=new QAction("2 X 2",this);
	menu->addAction(Action2x2);
	connect(Action2x2,SIGNAL(triggered()),this,SLOT(Set2D()));
	connect(Action2x2,SIGNAL(triggered()),m_2DViewer,SLOT(Set2X2()));
	QAction* Action3x3=new QAction("3 X 3",this);
	menu->addAction(Action3x3);
	connect(Action3x3,SIGNAL(triggered()),this,SLOT(Set2D()));
	connect(Action3x3,SIGNAL(triggered()),m_2DViewer,SLOT(Set3X3()));
	QAction* Action3DAndMPR=new QAction("3D&MPR",this);
	menu->addAction(Action3DAndMPR);
	connect(Action3DAndMPR,SIGNAL(triggered()),this,SLOT(Set3DAndMPR()));
	m_CanvasLayoutButton->setPopupMode(QToolButton::MenuButtonPopup   );
	m_CanvasLayoutButton->setMenu(menu);
	m_CanvasLayoutButton->setIcon(QIcon(":/ICON/Layout"));
	ui.mainToolBar->addWidget(m_CanvasLayoutButton);

	//////标注
	QToolButton *m_AnnotaionButton=new QToolButton(this);
	m_AnnotaionButton->setIcon(QIcon(":/ICON/Annotation"));
	connect(m_AnnotaionButton,SIGNAL(clicked()),m_2DViewer,SLOT(ShowAnnotaion()));
	ui.mainToolBar->addWidget(m_AnnotaionButton);
	
	/////是否同步
	m_IsSamize=0;
	m_ChainButton=new QToolButton(this);
	m_ChainButton->setIcon(QIcon(":/ICON/BrokenLink"));
	connect(m_ChainButton,SIGNAL(clicked()),m_2DViewer,SLOT(SetSamize()));
	connect(m_ChainButton,SIGNAL(clicked()),this,SLOT(SetSamize()));
	ui.mainToolBar->addWidget(m_ChainButton);

	
	m_MeasurementButton=new QToolButton(this);
	m_MeasurementButton->setIcon(QIcon(":/ICON/M_Hide"));
	m_MeasurementButton->setPopupMode(QToolButton::MenuButtonPopup   );
	QMenu* measuremenu=new QMenu(this);
	{
		QAction* a=new QAction("Delete Measurement",this);
		measuremenu->addAction(a);
		connect(a,SIGNAL(triggered()),m_2DViewer,SLOT(DeleteMeasurement()));
	}
	m_MeasurementButton->setMenu(measuremenu);
	connect(this->m_MeasurementButton,SIGNAL(clicked()),m_2DViewer,SLOT(SwitchMeasurementMode()));
	connect(this->m_MeasurementButton,SIGNAL(clicked()),this,SLOT(SwitchMeasurementMode()));
	ui.mainToolBar->addWidget(m_MeasurementButton);
	
	QHBoxLayout* MainLayout=new QHBoxLayout;
	ui.centralWidget->setLayout(MainLayout);

	m_FolderView=new amyFolderView(this);
	MainLayout->addWidget(m_FolderView);
	
	
	//m_CanvasLayout=new QGridLayout(this);
	//amyDICOMCanvas* canvas;
	//for(int i=0;i<9;i++)
	//{
	//	canvas=new amyDICOMCanvas(this);
	//	if(i!=0)
	//		canvas->hide();
	//	canvas->setAutoFillBackground(true);
	//	QPalette p = canvas->palette();
	//	p.setColor(QPalette::Window,QColor(0,0,0));
	//	canvas->setPalette(p);
	//	connect(canvas,SIGNAL(s_doubleclicked()),this,SLOT(Maximize()));
	//	connect(canvas->GetCubeLing(),SIGNAL(s_slicechanged(int)),this,SLOT(SamizeSlice(int)));
	//	connect(canvas->GetCubeLing(),SIGNAL(s_srcregionzoomed(int)),this,SLOT(SamizeZoom(int)));
	//	connect(canvas->GetCubeLing(),SIGNAL(s_srcregiontranslated(QPoint)),this,SLOT(SamizeTranslate(QPoint)));
	//	
	//	//connect(this->m_MeasurementButton,SIGNAL(clicked()),canvas->GetCubeLing(),SLOT(SwitchMode()));
	//	this->m_CanvasArr.push_back(canvas);
	//}
	//m_ActivatedCanvas=m_CanvasArr[0];
	MainLayout->addWidget(m_ViewerContainer);
	//QHBoxLayout* hl=new QHBoxLayout(this);
	//hl->setSpacing(0);
	//hl->setContentsMargins(0,0,0,0);
	//hl->addWidget(m_ViewerContainer);
	//MainLayout->addLayout(hl,Qt::AlignLeft|Qt::AlignHCenter|Qt::AlignVCenter);
	//MainLayout->addWidget(m_ViewerContainer);
	//for(int i=0;i<3;i++)
	//{
	//    for(int j=0;j<3;j++)
	//	{
	//	m_CanvasLayout->addWidget(this->m_CanvasArr[i+j*3],i,j);
	//	}
	//}
	
	QPalette p=this->palette();
	this->setAutoFillBackground(true);
	p = this->palette();
	//p.setColor(QPalette::Window,QColor(100,100,100));
	p.setColor(QPalette::Window,QColor(156,170,193));
	this->setPalette(p);
	

	
}

QAMYWindow::~QAMYWindow()
{

}

//void QAMYWindow::Set1X1()
//{
//	m_ViewerContainer->setCurrentIndex(0);
//	//m_LayoutType=LAYOUT_1X1;
//	//for(int i=0;i<3;i++)
//	//{
//	//	for(int j=0;j<3;j++)
//	//	{
//	//		this->m_CanvasArr[i+j*3]->hide();
//	//	}
//	//}
//	//if(m_ActivatedCanvas)
//	//	m_ActivatedCanvas->show();
//}
//void QAMYWindow::Set2X2()
//{
//	m_ViewerContainer->setCurrentIndex(0);
//	//m_LayoutType=LAYOUT_2X2;
//	//for(int i=0;i<3;i++)
//	//{
//	//	for(int j=0;j<3;j++)
//	//	{
//	//		if(i<2&&j<2)
//	//			this->m_CanvasArr[i+j*3]->show();
//	//		else
//	//		this->m_CanvasArr[i+j*3]->hide();
//	//	}
//	//}
//}
void QAMYWindow::Set2D()
{
	m_ViewerContainer->setCurrentIndex(0);
	//m_LayoutType=LAYOUT_3X3;
	//for(int i=0;i<3;i++)
	//{
	//	for(int j=0;j<3;j++)
	//	{
	//			this->m_CanvasArr[i+j*3]->show();
	//	}
	//}
}
void QAMYWindow::Set3DAndMPR()
{
	m_ViewerContainer->setCurrentIndex(1);
}
#define DEFAULT_DIR_KEY "DIE_KEY"
void QAMYWindow::OpenFolder()
{
	QSettings MySettings;
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),MySettings.value(DEFAULT_DIR_KEY).toString(),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if(dir=="")
		return;
	QByteArray ba = dir.toLocal8Bit();
	const char* path=ba.data();
	MySettings.setValue(DEFAULT_DIR_KEY,dir);
	amyDCMFolder *testf=new amyDCMFolder;
	testf->Open(path);
	testf->Parse();

	//amyPatient* debug=testf->GetPatientArr()[0].GetPointer();
	m_FolderView->SetFolder(testf);//内部有智能指针管理

}

void QAMYWindow::closeEvent(QCloseEvent *event)
{
	//QAMYVariableView::GetInstance()->close();

}
//bool ishow=1;
//void QAMYWindow::ShowAnnotaion()
//{
//	if(ishow)
//	{
//		for(int j=0;j<9;j++)
//		{
//			this->m_CanvasArr[j]->SetAnnotaion(0);
//		}
//		ishow=0;
//	}
//	else
//	{
//		for(int j=0;j<9;j++)
//		{
//			this->m_CanvasArr[j]->SetAnnotaion(1);
//		}
//		ishow=1;
//	}
//}

//void QAMYWindow::Maximize()
//{
//	static bool ismaximized=0;
//	if(!ismaximized)
//	{
//		for(int i=0;i<m_CanvasArr.size();i++)
//		{
//			this->m_CanvasArr[i]->hide();
//		}
//		amyDICOMCanvas* can=qobject_cast<amyDICOMCanvas*>(sender());
//		if(can!=0)
//		{
//			can->show();
//			m_ActivatedCanvas=can;
//		}
//		ismaximized=1;
//	}
//	else
//	{
//		switch(this->m_LayoutType)
//		{
//		case LAYOUT_1X1:
//			Set1X1();
//			break;
//		case LAYOUT_2X2:
//			Set2X2();
//			break;
//		case LAYOUT_3X3:
//			Set3X3();
//			break;
//		}
//		ismaximized=0;
//	}
//}
void QAMYWindow::SetSamize()
{
	m_IsSamize=m_IsSamize?0:1;
	if(m_IsSamize)
	{
		m_ChainButton->setIcon(QIcon(":/ICON/Link"));
	}
	else
		m_ChainButton->setIcon(QIcon(":/ICON/BrokenLink"));
}
//void QAMYWindow::SamizeSlice(int a)
//{ 
//	if(m_IsSamize==0)
//		return;
//	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
//	for(int i=0;i<m_CanvasArr.size();i++)
//	{
//		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
//		if(l!=cl)
//		{
//			if(l)
//			l->SetSllce(a);
//			m_CanvasArr[i]->UpdateAnnotation();
//		}
//	}
//}
//
//void QAMYWindow::SamizeZoom(int deg)
//{
//	if(m_IsSamize==0)
//		return;
//	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
//	for(int i=0;i<m_CanvasArr.size();i++)
//	{
//		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
//		if(l!=cl)
//		{
//			if(l)
//				l->ZoomSrcRect(deg);
//		}
//	}
//}
//void QAMYWindow::SamizeTranslate(QPoint p)
//{
//	if(m_IsSamize==0)
//		return;
//	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
//	for(int i=0;i<m_CanvasArr.size();i++)
//	{
//		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
//		if(l!=cl)
//		{
//			if(l)
//				l->TranslateSrcRect(p);
//		}
//	}
//}

void QAMYWindow::SwitchMeasurementMode()
{
	//for(int i=0;i<m_CanvasArr.size();i++)
	//{
	//	m_CanvasArr[i]->GetCubeLing()->SwitchMode();
	//}
	amyMeasureLing::eMode m=(amyMeasureLing::eMode)m_2DViewer->GetMeasureMode();
	if(m==amyMeasureLing::MODE_MEASURE_HIDE)
	{
		m_MeasurementButton->setIcon(QIcon(":/ICON/M_Hide"));
	}
	if(m==amyMeasureLing::MODE_MEASURE_DRAW)
	{
		m_MeasurementButton->setIcon(QIcon(":/ICON/M_Draw"));
	}
	if(m==amyMeasureLing::MODE_MEASURE_SHOW)
	{
		m_MeasurementButton->setIcon(QIcon(":/ICON/M_Show"));
	}
}
//void QAMYWindow::DeleteMeasurement()
//{
//	for(int i=0;i<m_CanvasArr.size();i++)
//	{
//		m_CanvasArr[i]->GetCubeLing()->ClearAll();
//	}
//}