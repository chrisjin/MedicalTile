#pragma once
#include"GuiMacro.h"
#include<vector>
#include<qwidget.h>
using namespace std;
class amyLing;
class GUI_INTERFACE amyCanvas:public QWidget
{
public:
	amyCanvas(QWidget *parent = 0);
	~amyCanvas();
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseLeaveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent * event);
	virtual void wheelEvent ( QWheelEvent * event );
	virtual void resizeEvent ( QResizeEvent * event );
	virtual void dropEvent(QDropEvent *event);
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void keyPressEvent ( QKeyEvent * event );
	void AddLing(amyLing* am);
	void paintEvent(QPaintEvent *);
	void RemoveLing(amyLing* am);
	void ReplaceLing(amyLing* replaced,amyLing* newling);
private:
	vector<amyLing*> m_LingArr;
};