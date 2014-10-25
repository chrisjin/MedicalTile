#pragma once
#include"amyLing.h"
#include"amyPure.h"
#include<QString>
class amyCubeLing;
class QPaintDevice;
class amyCanvas;
#include<QRect>
class GUI_INTERFACE amySelectionLing:public QObject,public amyLing
{
	Q_OBJECT
public:
	amySelectionLing(amyCanvas* can,QRect rect,QString text);
	void Render(QPaintDevice* dev);
	void SetRect(QRect r);
	void SetSelected(bool arg);
	void mouseMoveEvent(QMouseEvent * event); 
	void mousePressEvent(QMouseEvent * event);
signals:
	void s_selected();
private:
	bool m_IsSelected;
	bool m_IsHover;
	QString m_Text;
	QRect m_Rect;
};