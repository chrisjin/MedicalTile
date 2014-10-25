#include"amyGrid2DViewer.h"
#include"amyDICOMCanvas.h"
#include<QGridLayout>
#include"amyMeasureLing.h"
#include"amyAdvDICOMCanvas.h"
amyGrid2DViewer::amyGrid2DViewer(QWidget* p):QWidget(p)
{
	m_IsSamize=0;

	amyDICOMCanvas* canvas;
	for(int i=0;i<9;i++)
	{
		canvas=new amyAdvDICOMCanvas(this);
		if(i!=0)
			canvas->hide();
		//canvas->setAutoFillBackground(true);
		//QPalette p = canvas->palette();
		//p.setColor(QPalette::Window,QColor(0,0,0));
		//canvas->setPalette(p);
		connect(canvas,SIGNAL(s_doubleclicked()),this,SLOT(Maximize()));
		connect(canvas->GetCubeLing(),SIGNAL(s_slicechanged(int)),this,SLOT(SamizeSlice(int)));
		connect(canvas->GetCubeLing(),SIGNAL(s_srcregionzoomed(int)),this,SLOT(SamizeZoom(int)));
		connect(canvas->GetCubeLing(),SIGNAL(s_srcregiontranslated(QPoint)),this,SLOT(SamizeTranslate(QPoint)));
		
		//connect(this->m_MeasurementButton,SIGNAL(clicked()),canvas->GetCubeLing(),SLOT(SwitchMode()));
		this->m_CanvasArr.push_back(canvas);
	}
	m_ActivatedCanvas=m_CanvasArr[0];
	m_CanvasLayout=new QGridLayout(this);
	m_CanvasLayout->setContentsMargins(0,0,0,0);
	setLayout(m_CanvasLayout);
	for(int i=0;i<3;i++)
	{
	    for(int j=0;j<3;j++)
		{
		m_CanvasLayout->addWidget(this->m_CanvasArr[i+j*3],i,j);
		}
	}
	QPalette pa=this->palette();
	this->setAutoFillBackground(true);
	pa = this->palette();
	//p.setColor(QPalette::Window,QColor(100,100,100));
	pa.setColor(QPalette::Window,QColor(156,170,193));
	this->setPalette(pa);

	//this->Set3X3();
}
int amyGrid2DViewer::GetMeasureMode()
{
	return ((amyMeasureLing*)m_CanvasArr[0]->GetCubeLing())->GetMeasureMode();
}
void amyGrid2DViewer::SamizeSlice(int a)
{ 
	if(m_IsSamize==0)
		return;
	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
	for(int i=0;i<m_CanvasArr.size();i++)
	{
		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
		if(l!=cl)
		{
			if(l)
			l->SetSlice(a);
			//m_CanvasArr[i]->UpdateAnnotation();
		}
	}
}

void amyGrid2DViewer::Set1X1()
{
	m_LayoutType=LAYOUT_1X1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			this->m_CanvasArr[i+j*3]->hide();
		}
	}
	if(m_ActivatedCanvas)
		m_ActivatedCanvas->show();
}

void amyGrid2DViewer::Set2X2()
{
	m_LayoutType=LAYOUT_2X2;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i<2&&j<2)
				this->m_CanvasArr[i+j*3]->show();
			else
			this->m_CanvasArr[i+j*3]->hide();
		}
	}
}
void amyGrid2DViewer::Set3X3()
{
	m_LayoutType=LAYOUT_3X3;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
				this->m_CanvasArr[i+j*3]->show();
		}
	}
}

void amyGrid2DViewer::SamizeZoom(int deg)
{
	if(m_IsSamize==0)
		return;
	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
	for(int i=0;i<m_CanvasArr.size();i++)
	{
		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
		if(l!=cl)
		{
			if(l)
				l->ZoomSrcRect(deg);
		}
	}
}

void amyGrid2DViewer::SamizeTranslate(QPoint p)
{
	if(m_IsSamize==0)
		return;
	amyCubeLing* cl=qobject_cast<amyCubeLing* >(this->sender());
	for(int i=0;i<m_CanvasArr.size();i++)
	{
		amyCubeLing *l=m_CanvasArr[i]->GetCubeLing();
		if(l!=cl)
		{
			if(l)
				l->TranslateSrcRect(p);
		}
	}
}

void amyGrid2DViewer::SetSamize()
{
	m_IsSamize=m_IsSamize?0:1;
}

void amyGrid2DViewer::SwitchMeasurementMode()
{
	for(int i=0;i<m_CanvasArr.size();i++)
	{
		((amyMeasureLing*)m_CanvasArr[i]->GetCubeLing())->SwitchMode();
	}
}
void amyGrid2DViewer::DeleteMeasurement()
{
	for(int i=0;i<m_CanvasArr.size();i++)
	{
		((amyMeasureLing*)m_CanvasArr[i]->GetCubeLing())->ClearAll();
	}
}
bool ishow=1;
void amyGrid2DViewer::ShowAnnotaion()
{
	if(ishow)
	{
		for(int j=0;j<9;j++)
		{
			this->m_CanvasArr[j]->SetAnnotaion(0);
		}
		ishow=0;
	}
	else
	{
		for(int j=0;j<9;j++)
		{
			this->m_CanvasArr[j]->SetAnnotaion(1);
		}
		ishow=1;
	}
}
void amyGrid2DViewer::Maximize()
{
	static bool ismaximized=0;
	if(!ismaximized)
	{
		for(int i=0;i<m_CanvasArr.size();i++)
		{
			this->m_CanvasArr[i]->hide();
		}
		amyDICOMCanvas* can=qobject_cast<amyDICOMCanvas*>(sender());
		if(can!=0)
		{
			can->show();
			m_ActivatedCanvas=can;
		}
		ismaximized=1;
	}
	else
	{
		switch(this->m_LayoutType)
		{
		case LAYOUT_1X1:
			Set1X1();
			break;
		case LAYOUT_2X2:
			Set2X2();
			break;
		case LAYOUT_3X3:
			Set3X3();
			break;
		}
		ismaximized=0;
	}
}