#pragma once
#include"amyCubeLing.h"
#include<QPoint>
#include<QRect>
class GUI_INTERFACE amyROILing:public amyCubeLing
{
public:
	amyROILing(amyCanvas* can);
	virtual QImage DecorateImage(const QImage& image);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	QRect GetRect(){return m_ROIRect;}
	virtual void InitInput();
private:
	bool m_BeginToDraw;
	QPoint m_BeginPos;
	QRect m_ROIRect;
};
