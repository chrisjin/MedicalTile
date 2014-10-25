#pragma once
#include"amyLing.h"
class amyCanvas;
#include<vector>
using namespace std;
class GUI_INTERFACE amyGroupLing:public amyLing
{
public:
	amyGroupLing(amyCanvas* can);

	virtual void Render(QPaintDevice* dev);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseLeaveClientEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent * event);
	virtual void wheelEvent ( QWheelEvent * event );
	virtual void resizeEvent ( QResizeEvent * event );
	void AddLing(amyLing* am);
	void RemoveLing(amyLing* am);
private:
	vector<amyLing*> m_LingArr;
};