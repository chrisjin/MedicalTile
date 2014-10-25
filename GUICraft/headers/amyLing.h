#pragma once
#include"amyPure.h"
#include<qpaintdevice.h>
#include<qevent.h>
#include"amyCanvas.h"
#include"GuiMacro.h"
//class QMouseEvent;
//class QWheelEvent;
//class QPaintDevice;
class amyGroupLing;
class GUI_INTERFACE amyLing
{
public:
	amyLing(amyCanvas* can);
	void SetCanvas(amyCanvas* can);
	amyLing(amyGroupLing* gl);
	amyLing(const amyRect rect,amyCanvas* can=0);
	virtual ~amyLing(){}
	virtual void Render(QPaintDevice* dev){}
	virtual void mousePressEvent(QMouseEvent *event){}
	virtual void mouseMoveEvent(QMouseEvent * event){}
	virtual void mouseReleaseEvent(QMouseEvent *){}
	virtual void mouseLeaveClientEvent(QMouseEvent *){}
	virtual void mouseDoubleClickEvent(QMouseEvent * event){}
	virtual void wheelEvent ( QWheelEvent * event ){}
	virtual void resizeEvent ( QResizeEvent * event ){}
	virtual void dropEvent(QDropEvent *event){}
	virtual void dragEnterEvent(QDragEnterEvent *event){}
	virtual void keyPressEvent ( QKeyEvent * event ){}
	//virtual void Update();
	void SetRect(const amyRect& rect){m_Rect=rect;}
	void SetPosition(int x,int y){m_Rect.x=x;m_Rect.y=y;}
	void GetPosition(int&x,int&y){x=m_Rect.x;y=m_Rect.y;}
	void SetSize(int w,int h){m_Rect.width=w;m_Rect.height=h;}
	amyRect GetRect(){return m_Rect;}
	amyCanvas* GetCanvas(){return m_Canvas;}
	void Hide(){m_IsShow=0;}
	void Show(){m_IsShow=1;}
	bool IsShow(){return m_IsShow;}
	virtual bool IsContain(int x,int y);
	bool IsIn(const amyRect& rect);
private:
	bool    m_IsShow;
	amyRect m_Rect;
	amyCanvas* m_Canvas;
};