#include"amyMeasureLing.h"
#include<QPainter>
#include"Math.h"
#include"stdlib.h"
#include"amyCube.h"
#include"amyCubeLing.h"
amyMeasureLing::amyMeasureLing(amyCanvas* can):amyCubeLing(can)
{
	m_BeginToDraw=0;
	m_DoneDraw=0;
	m_Mode=MODE_MEASURE_HIDE;
	this->SetInput(0);
}
void amyMeasureLing::SetMeasureMode(eMode m)
{
	m_Mode=m;
}
void amyMeasureLing::SwitchMode()
{
	m_Mode=(eMode)((m_Mode+1)%3);
	this->GetCanvas()->repaint();
}

#define PickPointToDrawText(p1,p2) (p1.x()-p2.x()>0?p1:p2)
void amyMeasureLing::RenderOthers(QPaintDevice* dev)
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	if(this->m_MeasurementArr.size()==0)
		return;
	if(m_Mode==MODE_MEASURE_DRAW||m_Mode==MODE_MEASURE_SHOW)
	{
		QPainter p(dev);
		p.setRenderHint(QPainter::Antialiasing);
		QPen pen;
		pen.setColor(Qt::red);
		pen.setWidth(2);
		p.setPen(pen);
		QPoint TextPos;
		if(m_BeginToDraw)
		{
			QPoint p1=MapCube2Screen(m_BeginPos);
			QPoint p2=MapCube2Screen(m_EndPos);
			TextPos=PickPointToDrawText(p1,p2);
			p.drawLine(p1,p2);
			p.drawText(TextPos,m_Tag);
		}
		Measurement& m=this->m_MeasurementArr[this->GetSlice()];
		for(int i=0;i<m.m_P1Arr.size();i++)
		{
			QPoint p1=MapCube2Screen(m.m_P1Arr[i]);
			QPoint p2=MapCube2Screen(m.m_P2Arr[i]);
			p.drawLine(p1,p2);
			QFont font;
			font.setPixelSize(15);
			font.setBold(1);
			p.setFont(font);
			TextPos=PickPointToDrawText(p1,p2);
			p.drawText(TextPos,m.m_TagArr[i]);
		}
	}
}


void   amyMeasureLing::InitInput()
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	this->m_MeasurementArr.clear();
	amyCube::tCube::SpacingType sp=c->obj->GetSpacing();
	this->m_SpacingX=sp[0];
	this->m_SpacingY=sp[1];
	amyCube::tCube::RegionType region=c->obj->GetLargestPossibleRegion();
	int slicenum=region.GetSize()[2];
	for(int i=0;i<slicenum;i++)
	{
		Measurement m;
		this->m_MeasurementArr.push_back(m);
	}
	amyCubeLing::InitInput();
}
void amyMeasureLing::mousePressEvent(QMouseEvent *event)
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	if(event->buttons()&Qt::LeftButton&&m_BeginToDraw==0&&m_Mode==MODE_MEASURE_DRAW)
	{
		m_BeginToDraw=1;
		m_BeginPos=this->MapScreen2Cube(event->pos());
		m_EndPos=m_BeginPos;
		//m_P1.push_back(this->MapScreen2Cube(event->pos())
	}
	if(m_Mode==MODE_MEASURE_SHOW||m_Mode==MODE_MEASURE_HIDE||event->buttons()&Qt::MiddleButton)
	{
		amyCubeLing::mousePressEvent(event);
	}
}
void amyMeasureLing::mouseMoveEvent(QMouseEvent * event)
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	if(m_Mode==MODE_MEASURE_SHOW||m_Mode==MODE_MEASURE_HIDE||event->buttons()&Qt::MiddleButton)
	{
		amyCubeLing::mouseMoveEvent(event);
	}
	if(m_BeginToDraw&&m_Mode==MODE_MEASURE_DRAW)
	{
		QPoint cp=this->MapScreen2Cube(event->pos());
		m_EndPos=cp;
		QPoint DiffPos=m_EndPos-m_BeginPos;
		float l=CalDistance(m_EndPos,m_BeginPos);
		m_Tag=QString::number(l)+" mm";
	}
	Update();

}
void amyMeasureLing::mouseReleaseEvent(QMouseEvent *event)
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	if(m_BeginToDraw&&m_Mode==MODE_MEASURE_DRAW)
	{
		m_BeginToDraw=0;
		m_DoneDraw=1;
		QPoint cp=this->MapScreen2Cube(event->pos());
		m_EndPos=cp;
		float l=CalDistance(m_EndPos,m_BeginPos);
		m_Tag=QString::number(l)+" mm";


		this->m_MeasurementArr[this->GetSlice()].m_P1Arr.push_back(m_BeginPos);
		this->m_MeasurementArr[this->GetSlice()].m_P2Arr.push_back(m_EndPos);
		this->m_MeasurementArr[this->GetSlice()].m_TagArr.push_back(m_Tag);

		this->GetCanvas()->repaint();
	}
	if(m_Mode==MODE_MEASURE_SHOW||m_Mode==MODE_MEASURE_HIDE||event->button()==Qt::MiddleButton)
	{
		amyCubeLing::mouseReleaseEvent(event);
	}
}

void amyMeasureLing::ClearAll()
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	for(int i=0;i<this->m_MeasurementArr.size();i++)
	{
		this->m_MeasurementArr[i].m_P1Arr.clear();
		this->m_MeasurementArr[i].m_P2Arr.clear();
		this->m_MeasurementArr[i].m_TagArr.clear();
	}
	this->GetCanvas()->repaint();
}
float amyMeasureLing::CalDistance(QPoint p1,QPoint p2)
{
	QPoint DiffPos=p1-p2;
	float xl=DiffPos.x()*this->m_SpacingX;
	float yl=DiffPos.y()*this->m_SpacingY;
	float l=sqrt(xl*xl+yl*yl);
	return l;
}
