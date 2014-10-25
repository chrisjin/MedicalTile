#include"amyLing.h"
#include<qwidget.h>
#include"amyGroupLing.h"
amyLing::amyLing(amyCanvas* can)
{
	if(can==0)
		can=new amyCanvas;
	m_IsShow=1;
	can->AddLing(this);
	m_Canvas=can;
}
void amyLing::SetCanvas(amyCanvas* can)
{
	m_Canvas=can;
}
amyLing::amyLing(amyGroupLing* gl)
{
	m_IsShow=1;
	gl->AddLing(this);
	m_Canvas=gl->GetCanvas();
}
amyLing::amyLing(const amyRect rect,amyCanvas* can):m_Rect(rect)
{
	if(can==0)
		can=new amyCanvas;
	can->AddLing(this);
	m_Canvas=can;
}
bool amyLing::IsContain(int x,int y)
{
	amyRect rect=this->GetRect();
	if(x>=rect.x&&x<=rect.x+rect.width
		&&y>=rect.y&&y<=rect.y+rect.height)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
bool amyLing::IsIn(const amyRect& rect)
{
	amyRect r=this->GetRect();
	if(r.x>=rect.x&&r.x+r.width<=rect.x+rect.width
		&&r.y>=rect.y&&r.y+r.height<=rect.y+rect.height)
	return 1;
	else
		return 0;
}
