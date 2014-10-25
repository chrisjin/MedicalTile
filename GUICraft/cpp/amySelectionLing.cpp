#include"amySelectionLing.h"
#include<QPainter>
amySelectionLing::amySelectionLing(amyCanvas* can,QRect rect,QString text):amyLing(can)
{
	m_Text=text;
	m_IsSelected=0;
	m_Rect=rect;
	m_IsHover=0;
}
void amySelectionLing::Render(QPaintDevice* dev)
{
	QPainter p(dev);
	if(m_IsSelected==1)
		p.setPen(Qt::red);
	else
		p.setPen(Qt::green);
	QFont font;
	font.setStyleHint(QFont::Fantasy);
	font.setPixelSize(16);
	p.setFont(font);
	p.drawText(m_Rect,Qt::AlignCenter,m_Text);

	p.setPen(Qt::yellow);
	if(m_IsHover)
		p.drawRect(m_Rect);
}
void amySelectionLing::mouseMoveEvent(QMouseEvent * event)
{
	if(m_Rect.contains(event->pos()))
	{
		m_IsHover=1;
	}
	else
		m_IsHover=0;
}
void amySelectionLing::SetRect(QRect r)
{
	this->m_Rect=r;
	this->GetCanvas()->repaint();
}
void amySelectionLing::SetSelected(bool arg)
{
	this->m_IsSelected=arg;
}

void amySelectionLing::mousePressEvent(QMouseEvent * event)
{
	if(m_Rect.contains(event->pos()))
	{
		this->m_IsSelected=1;
		emit s_selected();
		this->GetCanvas()->repaint();
	}
}