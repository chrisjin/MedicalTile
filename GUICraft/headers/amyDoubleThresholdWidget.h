#pragma once
#include"GuiMacro.h"
#include<QWidget>
class QPaintEvent;
class GUI_INTERFACE amyDoubleThresholdWidget:public QWidget
{
	Q_OBJECT
public:
	amyDoubleThresholdWidget(Qt::Orientation o=Qt::Horizontal,QWidget* p=0);
	inline void SetStepCount(int a);
	 void SetBound(float low,float high);
	 void SetThreshold(float a,float b);
	 void SetHighThreshold(float a);
	 void SetLowThreshold (float a);
	inline void MoveThreshold(float a);
	inline void SetBarWidth(float a);
	inline QRect GetBarRect();
	int MapToView(float v);
	float MapFromView(int v);
	void paintEvent(QPaintEvent *);
	void UpdateRatio();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void resizeEvent( QResizeEvent * event );
	void GetThreshold(float& low,float& high);
signals:
	void s_thresholdchanging(float,float);
	void s_thresholdchanged(float,float);
private:
	int m_BeginToDragL;
	int m_BeginToDragH;
	Qt::Orientation m_Orientation;
	float m_Low;
	float m_High;
	float m_LThreshold;
	float m_HThreshold;
	float m_StepCount;
	float m_Ratio;
	float m_BarWidth;
	QRect m_BoundingRect;
};
