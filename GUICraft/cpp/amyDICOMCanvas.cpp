#include "amyDICOMCanvas.h"
#include"amyCubeLing.h"
#include"amyDragData.h"
#include"amyCube.h"
#include"amyDICOM.h"
#include"amyAnnotationLing.h"
#include"amyMeasureLing.h"
#include"amySeriesManager.h"
#include"amyShuttle.h"
#include"amyKeeper.h"
#include"amySelectionLing.h"
amyDICOMCanvas::amyDICOMCanvas(QWidget *parent) 
	: amyDropCanvas(parent)
{     
	m_CubeLing=new amyMeasureLing(this);
	//m_CubeLing->SetMeasureMode(amyMeasureLing::MODE_MEASURE_HIDE);
	m_CubeLing->SetInput(0);
	connect(m_CubeLing,SIGNAL(s_slicechanged(int)),this,SLOT(SliceChanged(int)));
	
	m_Annotation=new amyAnnotationLing(m_CubeLing,this);

	setAutoFillBackground(true);
	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(0,0,0));
	setPalette(p);
	setAcceptDrops(true);
	setMouseTracking(true);
}

amyDICOMCanvas::~amyDICOMCanvas()
{

}
void amyDICOMCanvas::ReplaceCubeLing(amyCubeLing* cubeling)
{
	if(m_CubeLing)
	{
		ReplaceLing(m_CubeLing,cubeling);
	}
	this->m_Annotation->SetCubeLing(cubeling);
	m_CubeLing=cubeling;
	m_CubeLing->SetInput(0);
}

void amyDICOMCanvas::SetView(amyUtil::ePlane p)
{
	this->m_CubeLing->SetView(p);
}

void amyDICOMCanvas::Clear()
{
	m_CubeLing->SetInput(0);
	//HideViewSelectionLing();
}

bool amyDICOMCanvas::IsAccept(VTYPE t)
{
	if(t==VTYPE_CUBE||t==VTYPE_SERIES)
		return 1;
	else
		return 0;
}
bool amyDICOMCanvas::OnAcceptSeries(amyKeeper<amySeries> k)
{
	amySeriesManager* sm=amySeriesManager::GetInstance();
	m_Cube=sm->GetCube(k);
	m_CubeLing->SetInput(m_Cube.GetPointer());
	return 1;
}
bool amyDICOMCanvas::OnAcceptCube(amyKeeper<amyCube> k)
{
	m_Cube=k;
	m_CubeLing->SetInput(m_Cube.GetPointer());
	return 1;
}

void amyDICOMCanvas::mouseDoubleClickEvent ( QMouseEvent * event )
{
	emit s_doubleclicked();
	amyCanvas::mouseDoubleClickEvent(event);
}

void amyDICOMCanvas::mouseMoveEvent(QMouseEvent * event)
{
	amyCube* cube=this->m_CubeLing->GetInput();
	if(!cube)
		return;
	if(cube->obj.IsNull())
		return;
	if(this->m_Annotation->IsShow())
	{
		QPoint p=this->m_CubeLing->MapScreen2Cube(QPoint(event->x(),event->y()));
		amyCube::tCube::IndexType index;
		index[0]=p.x();
		index[1]=p.y();
		index[2]=this->m_CubeLing->GetSlice();
		if(cube->obj->GetLargestPossibleRegion().IsInside(index))
			this->m_Annotation->SetPixelValue(p.x(),p.y(),cube->obj->GetPixel(index),1);
		else
			this->m_Annotation->SetPixelValue(0,0,0,0);
		repaint();
	}
	amyCanvas::mouseMoveEvent(event);
	if(event->buttons()&Qt::RightButton)
	{
		int c,w;
		m_CubeLing->GetWindow(c,w);
		m_Annotation->SetWindow(c,w);
	}
	else if(event->buttons()&Qt::LeftButton)
	{
		m_Annotation->SetSlice(m_CubeLing->GetSlice());
	}
	
}

void amyDICOMCanvas::SetAnnotaion(bool is)
{
	if(!this->m_Annotation)
		return;
	if(is)
	{
		this->m_Annotation->Show();
	}
	else
	{
		this->m_Annotation->Hide();
	}
	repaint();
}

//void amyDICOMCanvas::SliceChanged(int s)
//{
//	m_Annotation->SetSlice(s);
//}
//void amyDICOMCanvas::UpdateAnnotation()
//{
//	m_Annotation->SetSlice(m_CubeLing->GetSlice());
//}
