#pragma once
#include<QObject>
#include"amyPure.h"
#include<QWidget>
#include<vector>
#include"amyArray.h"
#include"amyKeeper.h"
#include<QColor>
using namespace std;


typedef amyPoint         tPoint;
struct _Curve
{
	vector<tPoint> pointarr;
	QColor         color;
};
typedef _Curve   tCurve;
//typedef vector<tPoint>   tCurve;
typedef vector<amyKeeper<tCurve>>  tCurveArr;


class DataModel:public QObject
{
	Q_OBJECT
public:
	enum Axis{X,Y,NONE};
	vector<Axis> axisrole;
	vector<int>  pairrole;
	vector<QColor> colorrole;
	vector<amyKeeper<amyArray>> totaldata;
	void Notify();
signals:
	void s_changed();
};

class amyDataWidget:public QWidget
{
	Q_OBJECT
public:
	amyDataWidget(QWidget* parent=0);
	void	SetModel(amyKeeper<DataModel> model);
	void	paintEvent(QPaintEvent *dev);
	void	resizeEvent ( QResizeEvent * event );
	void	mousePressEvent(QMouseEvent *event);
	void	mouseMoveEvent(QMouseEvent *event);
	void	mouseReleaseEvent(QMouseEvent *event);
	void	Crop();
	int		MapToWidgetX(float num);
	int		MapToWidgetY(float num);
	float	MapFromWidgetX(int num);
	float	MapFromWidgetY(int num);
	void	UpdateChartBound();
	void	GetXYRange(float& xmin,float& xman,float& ymin,float& ymax);
public slots:
	void Update();
	void XThresholdChanging(float,float);
	void XThresholdChanged(float,float);
	void YThresholdChanging(float,float);
	void YThresholdChanged(float,float);
signals:
	void s_xyrangechanged();
private:
	QRect m_Frame;
	float m_XRatio;
	float m_YRatio;
	amyKeeper<DataModel> m_DataModel;
	tCurveArr            m_CurveArr;
	float m_XMax;
	float m_XMin;
	float m_YMax;
	float m_YMin;
	float m_XTrLow;
	float m_YTrLow;
	float m_XTrHigh;
	float m_YTrHigh;
	bool  m_XShowLine;
	bool  m_YShowLine;
	//float m_
};

