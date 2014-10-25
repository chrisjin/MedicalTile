#include"amyMPRLineCubeLing.h"
#include<QPainter>
#define RANGE (3)
amyMPRLineCubeLing::amyMPRLineCubeLing(amyCanvas* p):amyCubeLing(p)
{
	this->m_VerticalLinePosition=1;
	this->m_HorizontalLinePosition=1;
	this->m_HorizontalLineColor=Qt::red;
	this->m_VerticalLineColor=Qt::green;
	m_IsDragHorizontal=0;
	m_IsDragVertical=0;
	//m_Orientation=Qt::Horizontal;
}
void amyMPRLineCubeLing::SetLineColor(Qt::Orientation type,QColor c)
{
	if(type==Qt::Horizontal)
	{
		this->m_HorizontalLineColor=c;
	}
	else
	{
		this->m_VerticalLineColor=c;
	}
}
void amyMPRLineCubeLing::SetLinePos(Qt::Orientation type,int pos)
{
	if(type==Qt::Horizontal)
	{
		int num=this->GetSliceHeight();
		if(pos>=0&&pos<num)
			this->m_HorizontalLinePosition=pos;
	}
	else if(type==Qt::Vertical)
	{
		int num=this->GetSliceWidth();
		if(pos>=0&&pos<num)
			this->m_VerticalLinePosition=pos;
	}
}
void amyMPRLineCubeLing::mousePressEvent(QMouseEvent *event)
{
	QPoint pos=this->MapScreen2Cube(event->pos());
	
	int flag;
	flag=abs(pos.y()-m_HorizontalLinePosition);
	if(flag<RANGE)
	{
		m_IsDragHorizontal=1;
		return;
	}
	flag=abs(pos.x()-m_VerticalLinePosition);
	if(flag<RANGE)
	{
		m_IsDragVertical=1;
		return;
	}
	if(flag>=RANGE)
	{
		amyCubeLing::mousePressEvent(event);
	}

}
void amyMPRLineCubeLing::mouseMoveEvent(QMouseEvent * event)
{
	QPoint pos=this->MapScreen2Cube(event->pos());
	if(this->GetMode()!=amyCubeLing::MODE_SLICE)
	{
		int flag;
		flag=abs(pos.y()-m_HorizontalLinePosition);
		if(flag<RANGE)
		{
			this->GetCanvas()->setCursor(Qt::CursorShape::SizeVerCursor);
		}
		else if(flag>=RANGE)
		{
			this->GetCanvas()->setCursor(Qt::CursorShape::ArrowCursor);
			flag=abs(pos.x()-m_VerticalLinePosition);
			if(flag<RANGE)
			{
				this->GetCanvas()->setCursor(Qt::CursorShape::SizeHorCursor);
			}
			else if(flag>=RANGE)
			{
				this->GetCanvas()->setCursor(Qt::CursorShape::ArrowCursor);
			}
		}

	}
	if(m_IsDragHorizontal)
	{
		m_HorizontalLinePosition=pos.y();
		emit s_horizontalposchanged(m_HorizontalLinePosition);
		this->GetCanvas()->repaint();
	}
	else if(m_IsDragVertical)
	{
		m_VerticalLinePosition=pos.x();
		emit s_verticalposchanged(m_VerticalLinePosition);
		this->GetCanvas()->repaint();
	}
	else
	{
		amyCubeLing::mouseMoveEvent(event);
	}
}
void amyMPRLineCubeLing::mouseReleaseEvent(QMouseEvent *event)
{
	m_IsDragHorizontal=0;
	m_IsDragVertical=0;
	amyCubeLing::mouseReleaseEvent(event);

}
void amyMPRLineCubeLing::RenderOthers(QPaintDevice* dev)
{
	QPoint pos1,pos2;
	QPoint scpos1,scpos2;
	QPainter p(dev);
	QPen pen;
	pen.setWidth(2);
	//if(m_Orientation==Qt::Vertical)
	//{
	pos1=QPoint(m_VerticalLinePosition,0);
	pos2=QPoint(m_VerticalLinePosition,this->GetSliceHeight());
	scpos1=this->MapCube2Screen(pos1);
	scpos2=this->MapCube2Screen(pos2);
	pen.setBrush(this->m_VerticalLineColor);
	p.setPen(pen);
	p.drawLine(scpos1,scpos2);
	//}
	//else if(m_Orientation==Qt::Horizontal)
	//{
	pos1=QPoint(0,m_HorizontalLinePosition);
	pos2=QPoint(this->GetSliceWidth(),m_HorizontalLinePosition);
	scpos1=this->MapCube2Screen(pos1);
	scpos2=this->MapCube2Screen(pos2);

	pen.setBrush(this->m_HorizontalLineColor);
	p.setPen(pen);
	p.drawLine(scpos1,scpos2);
	
	QString text;
	pen.setWidth(3);
	switch(this->GetView())
	{
	case amyUtil::AXIAL:
		pen.setBrush(Qt::red);
		p.setPen(pen);
		text="Axi";
		break;
	case amyUtil::CORONAL:
		pen.setBrush(Qt::green);
		p.setPen(pen);
		text="Cor";
		break;
	case amyUtil::SAGITTAL:
		pen.setBrush(Qt::blue);
		p.setPen(pen);
		text="Sag";
		break;
	}
	QRect r=this->GetCanvas()->rect();
	int bo=r.bottom();
	int ri=r.right();
	int spacing=3;
	int eachwidth=32;
	int eachheight=16;
	int cx=ri-eachwidth-spacing;
	int cy=bo-eachheight-spacing;
	QRect rtodraw=QRect(cx,cy,eachwidth,eachheight);
	p.drawRect(rtodraw);
	p.drawText(rtodraw,Qt::AlignCenter,text);
}