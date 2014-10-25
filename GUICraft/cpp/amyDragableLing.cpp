#include"amyDragableLing.h"
#include"amyCanvas.h"
amyDragableLing::amyDragableLing(amyCanvas* can):amyLing(can)
{
	m_BeginToDrag=0;
	m_Difx=0;
	m_Dify=0;
}
amyDragableLing::amyDragableLing(amyGroupLing* can):amyLing(can)
{
	m_BeginToDrag=0;
	m_Difx=0;
	m_Dify=0;
}
void amyDragableLing::mousePressEvent(QMouseEvent *event)
{
	if(this->IsContain(event->x(),event->y())&&m_BeginToDrag==0)
	{
		QPoint p=InitReferencePoint();
		m_Difx=event->x()-p.x();
		m_Dify=event->y()-p.y();
		m_BeginToDrag=1;
	}
	else
	{
		//this->SetActivated(0);
	}
}
void amyDragableLing::mouseMoveEvent(QMouseEvent * event)
{
	if(m_BeginToDrag)
	{
		OnUpdateReferencePoint(QPoint(event->x()-m_Difx,event->y()-m_Dify));
		this->GetCanvas()->repaint();
	}
}
void amyDragableLing::mouseReleaseEvent(QMouseEvent *)
{
	m_BeginToDrag=0;
}
void amyDragableLing::mouseLeaveClientEvent(QMouseEvent *)
{
	m_BeginToDrag=0;
}

amyRectDragableLing::amyRectDragableLing(amyCanvas* can):amyDragableLing(can)
{

}

QPoint amyRectDragableLing::InitReferencePoint()
{
	amyRect r=this->GetRect();
	return QPoint(r.x,r.y);
}
void   amyRectDragableLing::OnUpdateReferencePoint(QPoint p)
{
	this->SetPosition(p.x(),p.y());
}