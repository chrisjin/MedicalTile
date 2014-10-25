#include"amyDoubleThresholdWidget.h"
#include<QPainter>
#include<QGraphicsScene>
#include<QGraphicsWidget>
#include<QLabel>
#include<QGraphicsProxyWidget>
#include<QBoxLayout>
amyDoubleThresholdWidget::amyDoubleThresholdWidget(Qt::Orientation o,QWidget* p):QWidget(p)
{
	this->m_Orientation=o;
	m_StepCount=100;
	m_Low=0;
	m_High=100;
	m_BarWidth=50;
	this->setMouseTracking(true);
	m_BeginToDragH=0;
	m_BeginToDragL=0;
	
	QPalette pal=this->palette();
	this->setAutoFillBackground(true);
	pal = this->palette();
	pal.setColor(QPalette::Window,QColor(100,100,100));
	this->setPalette(pal);
}
void amyDoubleThresholdWidget::SetStepCount(int a)
{
	m_StepCount=a;
}
void amyDoubleThresholdWidget::SetBound(float low,float high)
{
	m_Low=low;
	m_High=high;
	UpdateRatio();
}
void amyDoubleThresholdWidget::SetThreshold(float a,float b)
{
	m_HThreshold=b;
	m_LThreshold=a;
}
void amyDoubleThresholdWidget::GetThreshold(float& low,float& high)
{
	high=m_HThreshold;
	low=m_LThreshold;
}
void amyDoubleThresholdWidget::UpdateRatio()
{
	float v;
	if(m_Orientation==Qt::Horizontal)
	{
		v=this->rect().width();
	}
	else if(m_Orientation==Qt::Vertical)
	{
		v=this->rect().height();
	}
	if(v==0)
		v=0.01;
	m_Ratio=(m_High-m_Low)/v;
	if(m_Ratio==0)
		m_Ratio=0.01;
}


void amyDoubleThresholdWidget::SetHighThreshold(float a)
{
	m_HThreshold=a;
}
void amyDoubleThresholdWidget::SetLowThreshold (float a)
{
	m_LThreshold=a;
}
void amyDoubleThresholdWidget::MoveThreshold(float a)
{
	m_HThreshold+=a;
	m_LThreshold+=a;
}
void amyDoubleThresholdWidget::SetBarWidth(float a)
{
	m_BarWidth=a;
}
//QRect amyDoubleThresholdItem::GetBoundingRect()const 
//{
//	//if(!m_BoundingRect.isValid())
//	//{
//	//	float left,right,top,bottom;
//	//	m_BarWidth=(m_High-m_Low)/50;
//	//	if(m_Orientation==Qt::Horizontal)
//	//	{
//	//		left=m_Low;
//	//		right=m_High;
//	//		top=m_BarWidth/2.0;
//	//		bottom=-m_BarWidth/2.0;
//	//	}
//	//	else if(m_Orientation==Qt::Vertical)
//	//	{
//	//		left=m_BarWidth/2.0;
//	//		right=-m_BarWidth/2.0;
//	//		top=m_High;
//	//		bottom=m_Low;
//	//	}
//	//	m_BoundingRect=QRect(left,bottom,right-left,top-bottom);
//	//}
//	return m_BoundingRect;
//}
QRect amyDoubleThresholdWidget::GetBarRect()
{
	QRect Bar=this->rect();
	if(m_Orientation==Qt::Horizontal)
	{
		Bar.setLeft(MapToView(m_LThreshold));
		Bar.setRight(MapToView(m_HThreshold));
	}
	else if(m_Orientation==Qt::Vertical)
	{
		Bar.setTop(MapToView(m_HThreshold));
		Bar.setBottom(MapToView(m_LThreshold));
	}
	return Bar;
}
int amyDoubleThresholdWidget::MapToView(float v)
{
	float ret;
	if(m_Orientation==Qt::Horizontal)
		ret=(v-m_Low)/m_Ratio+this->rect().left();
	else if(m_Orientation==Qt::Vertical)
		ret=this->rect().bottom()-(v-m_Low)/m_Ratio;
	return ret;
}
float amyDoubleThresholdWidget::MapFromView(int v)
{
	float ret;
	if(m_Orientation==Qt::Horizontal)
		ret=(v-this->rect().left())*m_Ratio+m_Low;
	else if(m_Orientation==Qt::Vertical)
		ret=(this->rect().bottom()-v)*m_Ratio+m_Low;
	return ret;
}
void amyDoubleThresholdWidget::mousePressEvent(QMouseEvent *event)
{
	int dif1,dif2;
	int v1=MapToView(m_LThreshold);
	int v2=MapToView(m_HThreshold);
	if(this->m_Orientation==Qt::Horizontal)
	{
		dif1=abs(v1-event->pos().x());
		dif2=abs(v2-event->pos().x());
	}
	else
	{
		dif1=abs(v1-event->pos().y());
		dif2=abs(v2-event->pos().y());
	}
	if(dif1<5)
	{
		m_BeginToDragL=1;
	}
	else if(dif2<5)
	{
		m_BeginToDragH=1;
	}
}
void amyDoubleThresholdWidget::mouseReleaseEvent(QMouseEvent *event)
{
	s_thresholdchanged(m_LThreshold,m_HThreshold);
	m_BeginToDragL=0;
	m_BeginToDragH=0;
}
void amyDoubleThresholdWidget::resizeEvent( QResizeEvent * event )
{
	UpdateRatio();
}
void amyDoubleThresholdWidget::mouseMoveEvent(QMouseEvent *event)
{
	int v1=MapToView(m_LThreshold);
	int v2=MapToView(m_HThreshold);
	float value;
	int dif1,dif2;
	if(this->m_Orientation==Qt::Horizontal)
	{
		dif1=abs(v1-event->pos().x());
		dif2=abs(v2-event->pos().x());
		value=MapFromView(event->pos().x());
	}
	else
	{
		dif1=abs(v1-event->pos().y());
		dif2=abs(v2-event->pos().y());
		value=MapFromView(event->pos().y());
	}
	if(dif1<5||dif2<5||m_BeginToDragH||m_BeginToDragL)
	{
		if(m_Orientation==Qt::Horizontal)
			this->setCursor(Qt::CursorShape::SizeHorCursor);
		if(m_Orientation==Qt::Vertical)
			this->setCursor(Qt::CursorShape::SizeVerCursor);
	}
	else
		this->setCursor(Qt::CursorShape::ArrowCursor);

	if(m_BeginToDragH)
	{
		if(value>=m_Low&&value<=m_High)
		m_HThreshold=value;
		if(m_HThreshold<m_LThreshold)
		{
			float a=m_HThreshold;
			m_HThreshold=m_LThreshold;
			m_LThreshold=a;
		}
		this->repaint();
		emit s_thresholdchanging(m_LThreshold,m_HThreshold);
	}
	else if(m_BeginToDragL)
	{
		if(value>=m_Low&&value<=m_High)
		m_LThreshold=value;
		if(m_HThreshold<m_LThreshold)
		{
			float a=m_HThreshold;
			m_HThreshold=m_LThreshold;
			m_LThreshold=a;
		}
		this->repaint();	
		emit s_thresholdchanging(m_LThreshold,m_HThreshold);
	}
}
void amyDoubleThresholdWidget::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	QRect r=GetBarRect();
	QRect T1;
	QRect T2;
	QRect wholerect=this->rect();
	if(m_Orientation==Qt::Horizontal)
	{
		T1.setTopLeft(r.topLeft());
		T1.setSize(QSize(40,wholerect.height()));
		T2.setTopLeft(r.topRight()-QPoint(40,0));
		T2.setSize(QSize(40,wholerect.height()));
	}
	if(m_Orientation==Qt::Vertical)
	{
		T1.setTopLeft(r.bottomLeft()-QPoint(0,20));
		T1.setSize(QSize(wholerect.width(),20));
		T2.setTopLeft(r.topLeft());
		T2.setSize(QSize(wholerect.width(),20));
	}

	
	p.fillRect(r,Qt::red);
	if(r.contains(T1))
		p.setPen(Qt::yellow);
	else
		p.setPen(Qt::black);
	QString str=QString::number(m_LThreshold);
	if(str.size()>=4)
	str.truncate(6);
	QFlags<Qt::AlignmentFlag> F1;
	if(m_Orientation==Qt::Horizontal)
		F1=Qt::AlignLeft|Qt::AlignVCenter;
	else
		F1=Qt::AlignBottom|Qt::AlignHCenter;
	p.drawText(T1,F1,str);

	if(r.contains(T2))
		p.setPen(Qt::yellow);
	else
		p.setPen(Qt::black);
	str=QString::number(m_HThreshold);
	if(str.size()>=4)
	str.truncate(6);
	QFlags<Qt::AlignmentFlag> F2;
	if(m_Orientation==Qt::Horizontal)
		F2=Qt::AlignRight|Qt::AlignVCenter;
	else
		F2=Qt::AlignTop|Qt::AlignHCenter;
	p.drawText(T2,F2,str);


	p.setPen(Qt::PenStyle::DashDotLine);
	p.drawRect(wholerect);
}

