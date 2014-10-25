#pragma once
#include"amyCubeLing.h"
#include<QColor>
#include<QObject>
class amyCanvas;
class amyMPRLineCubeLing:public amyCubeLing
{
	Q_OBJECT
public:
	amyMPRLineCubeLing(amyCanvas* p=0);
	void		   SetLineColor(Qt::Orientation type,QColor c);
	void           SetLinePos(Qt::Orientation type,int pos);
	virtual void   RenderOthers(QPaintDevice* dev);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *);
private:
	int m_VerticalLinePosition;
	int m_HorizontalLinePosition;
	QColor m_VerticalLineColor;
	QColor m_HorizontalLineColor;
	Qt::Orientation m_Orientation;
	bool m_IsDragHorizontal;
	bool m_IsDragVertical;
signals:
	void s_verticalposchanged(int);
	void s_horizontalposchanged(int);

};