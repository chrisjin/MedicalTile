#include"amyROILing.h"
#include<QPainter>
amyROILing::amyROILing(amyCanvas* can):amyCubeLing(can)
{
	m_BeginToDraw=0;
}
void amyROILing::InitInput()
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	amyCube::tCube::RegionType reg=cube->obj->GetLargestPossibleRegion();
	amyCube::tCube::SizeType size=reg.GetSize();
	amyCube::tCube::IndexType index=reg.GetIndex();
	this->m_ROIRect=QRect(index[0],index[1],size[0],size[1]);
	amyCubeLing::InitInput();
}
QImage amyROILing::DecorateImage(const QImage& image)
{
	QImage img=QImage(image.width(),image.height(),QImage::Format_ARGB32);
	QPainter p(&img);
	//p.setPen(Qt::yellow);
	p.drawImage(QPoint(0,0),image);
	p.setPen(Qt::red);
	p.drawRect(m_ROIRect);
	return img;
}

void amyROILing::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons()&Qt::LeftButton)
	{
		if(m_BeginToDraw==0)
		{
			m_BeginPos=this->MapScreen2Cube(event->pos());

		}
		m_BeginToDraw=1;
	}
	amyCubeLing::mousePressEvent(event);
}
void amyROILing::mouseMoveEvent(QMouseEvent * event)
{
	amyCubeLing::mouseMoveEvent(event);
	if(event->buttons()&Qt::LeftButton)
	{
		if(m_BeginToDraw)
		{
			QPoint cp=MapScreen2Cube(event->pos());
			int x1=m_BeginPos.x()<cp.x()?m_BeginPos.x():cp.x();
			int y1=m_BeginPos.y()<cp.y()?m_BeginPos.y():cp.y();
			int x2=m_BeginPos.x()>cp.x()?m_BeginPos.x():cp.x();
			int y2=m_BeginPos.y()>cp.y()?m_BeginPos.y():cp.y();
			m_ROIRect.setTopLeft(QPoint(x1,y1));
			m_ROIRect.setBottomRight(QPoint(x2,y2));
		}
	}
	Update();
} 
void amyROILing::mouseReleaseEvent(QMouseEvent *event)
{
	m_BeginToDraw=0;
	amyCubeLing::mouseReleaseEvent(event);
}