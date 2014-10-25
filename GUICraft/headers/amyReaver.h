#pragma once
#include<QObject>
#include<QPoint>
#include"GuiMacro.h"
class QMouseEvent;
class amyReaver;
class GUI_INTERFACE amyScarab:public QObject
{
public:
	enum eMode
	{
		MODE_INSTANT,
		MODE_CROSSBOUNDARY
	};
	amyScarab(QObject* target,amyReaver* host);
	amyScarab(amyReaver* host);
public:
	void SetMode(eMode m);
	void SetSender(QObject* target);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
	void _mousePressEvent(QMouseEvent *event);
	void _mouseMoveEvent(QMouseEvent *event);
	void _mouseLeaveEvent(QMouseEvent *event);
private:
	amyReaver* m_Host;
	QObject*   m_Target;
	QPoint     m_StartPoint;
	eMode      m_Mode;
};
class GUI_INTERFACE amyReaver
{
public:
	amyReaver(QObject* target);
	amyReaver();
	void     SetSender(QObject* obj);
	virtual void OnTakeOff(QPoint pos)=0;
	virtual ~amyReaver();
private:
	amyScarab* m_Scarab;
};