#pragma once
#include"amyDragableLing.h"
#include"amyPure.h"
#include<QPoint>

class amyCube;
#include<vector>
#include<QObject>
using namespace std;
#include"amyGroupLing.h"
#include"amyCubeLing.h"
class amyGroupLing;
#include<QImage>
class GUI_INTERFACE Measurement
{
public:
	vector<QPoint> m_P1Arr;
	vector<QPoint> m_P2Arr;
	vector<QString> m_TagArr;
};
class GUI_INTERFACE amyMeasureLing:public amyCubeLing
{
	Q_OBJECT
public:
	enum eMode
	{
		MODE_MEASURE_HIDE,
		MODE_MEASURE_DRAW,
		MODE_MEASURE_SHOW
	};
	amyMeasureLing(amyCanvas* can);
	virtual void   mousePressEvent(QMouseEvent *event);
	virtual void   mouseMoveEvent(QMouseEvent * event);
	virtual void   mouseReleaseEvent(QMouseEvent *);
	virtual void   RenderOthers(QPaintDevice* dev);
	virtual void   InitInput();
	void		   SetMeasureMode(eMode m);
	eMode          GetMeasureMode(){return m_Mode;}
	void           ClearAll();
	float          CalDistance(QPoint p1,QPoint p2);
public slots:
	void           SwitchMode();
private:
	vector<Measurement> m_MeasurementArr;
	QPoint  m_BeginPos;
	QPoint  m_EndPos;
	QString m_Tag;
	float  m_SpacingX;
	float  m_SpacingY;
	bool   m_BeginToDraw;
	bool   m_DoneDraw;
	eMode  m_Mode;
};
