#include"amyReaver.h"
#include<QEvent>
#include<QMouseEvent>
#include<QApplication>
amyScarab::amyScarab(QObject* target,amyReaver* host)
{
	m_Host=host;
	m_Target=target;
	m_Mode=MODE_INSTANT;
	target->installEventFilter(this);
}
amyScarab::amyScarab(amyReaver* host)
{
	m_Host=host;
	m_Target=0;
	m_Mode=MODE_INSTANT;
}
void amyScarab::SetSender(QObject* target)
{
	m_Target=target;
	target->installEventFilter(this);
}
void amyScarab::SetMode(eMode m)
{
	m_Mode=m;
}
bool amyScarab::eventFilter(QObject *obj, QEvent *event)
{
	if(m_Target==obj)
	{
		QEvent::Type t=event->type();
		if(event->type()==QEvent::MouseMove&&m_Mode==MODE_INSTANT)
		{
			_mouseMoveEvent(static_cast<QMouseEvent*>(event));
		}
		if(event->type()==QEvent::MouseButtonPress&&m_Mode==MODE_INSTANT)
		{
			_mousePressEvent(static_cast<QMouseEvent*>(event));
		}
		if(event->type()==QEvent::Leave&&m_Mode==MODE_CROSSBOUNDARY)
		{
			_mouseLeaveEvent(static_cast<QMouseEvent*>(event));
		}
	}
	return QObject::eventFilter(obj,event);
}
void amyScarab::_mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_StartPoint=event->pos();
	}
}
void amyScarab::_mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) 
	{  
		int distance = (event->pos() - m_StartPoint).manhattanLength();  
		if (distance >= QApplication::startDragDistance()) 
		{
			m_Host->OnTakeOff(m_StartPoint);
		}
	}
}
void amyScarab::_mouseLeaveEvent(QMouseEvent *event)
{
	m_Host->OnTakeOff(m_StartPoint);
}

amyReaver::~amyReaver()
{
	delete m_Scarab;
}
amyReaver::amyReaver()
{
	m_Scarab=new amyScarab(this);
}
amyReaver::amyReaver(QObject* target)
{
	m_Scarab=new amyScarab(target,this);
}
void amyReaver::SetSender(QObject* obj)
{
	m_Scarab->SetSender(obj);
}