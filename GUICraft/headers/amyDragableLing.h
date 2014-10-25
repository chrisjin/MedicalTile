#pragma once
#include"amyLing.h"
class amyCanvas;
class amyGroupLing;
class GUI_INTERFACE amyDragableLing:public amyLing
{
public:
	amyDragableLing(amyCanvas* can=0);
	amyDragableLing(amyGroupLing* can);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseLeaveClientEvent(QMouseEvent *);
	virtual QPoint InitReferencePoint()=0;
	virtual void   OnUpdateReferencePoint(QPoint)=0;
private:
	bool m_BeginToDrag;
	int  m_Difx;
	int  m_Dify;
};

class GUI_INTERFACE amyRectDragableLing:public amyDragableLing
{
public:
	amyRectDragableLing(amyCanvas* can=0);
	virtual QPoint InitReferencePoint();
	virtual void   OnUpdateReferencePoint(QPoint);
};
