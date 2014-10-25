#pragma once
#include"amyImageLing.h"
#include<QObject>
#include"amyPure.h"
#include"amyUtil.h"
class amyCanvas;
class amyCube;
class GUI_INTERFACE amyZoomLing:public QObject,public amyImageLing,public amyInput<amyCube*>
{
	Q_OBJECT
public:
	amyZoomLing(amyCanvas* can);
	void wheelEvent ( QWheelEvent * event );
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent*);

	QRect GetDesRect();
	QRect GetSrcRect(){return m_SrcRect;}
	QPoint MapScreen2Cube(QPoint screen);
	QPoint MapCube2Screen(QPoint cube);
	void TranslateSrcRect(QPoint p);
	void ZoomSrcRect(int deg);
	void InitImage(QImage& image);
	void InitInput();
	void RenderImage(QPaintDevice* dev,const QPixmap& pix);

	void FitImageToRect();

	amyUtil::ePlane GetView(){return m_View;}
	amyUtil::ePlane GetInputView(){return m_InputView;}
	void SetView(amyUtil::ePlane v);
	bool IsOriginalView();
private:
	amyUtil::ePlane  m_View;
	amyUtil::ePlane             m_InputView;
	QImage Image;
	QRect  m_DesRect;        //
	QRect  m_SrcRect;
	//QRect  m_ViewPort;
	QRect  m_MaxSrcRect;  //Í¼Ïñ×î´ó·¶Î§
	bool   m_IsBeginToPan;
	QPoint m_LastPoint;
signals:
	void s_srcregiontranslated(QPoint);
	void s_srcregionzoomed(int);
};