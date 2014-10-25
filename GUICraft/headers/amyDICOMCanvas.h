#ifndef AMYDICOMCANVAS_H
#define AMYDICOMCANVAS_H
#include"GuiMacro.h"
#include "amyCanvas.h"
#include"amyKeeper.h"
#include"amySelectionLing.h"
#include"amyUtil.h"
#include"amyDropCanvas.h"
class amyCubeLing;
class amyCube;
class amyAnnotationLing;
class amyMeasureLing;
class amySelectionLing;
class GUI_INTERFACE amyDICOMCanvas : public amyDropCanvas
{
	Q_OBJECT

public:
	amyDICOMCanvas(QWidget *parent=0);
	~amyDICOMCanvas();
	//void dropEvent(QDropEvent *event);
	//void dragEnterEvent(QDragEnterEvent *event);
	bool IsAccept(VTYPE t);
	virtual bool OnAcceptSeries(amyKeeper<amySeries> k);
	virtual bool OnAcceptCube(amyKeeper<amyCube> k);
	void mouseDoubleClickEvent ( QMouseEvent * event );
	void mouseMoveEvent(QMouseEvent * event);
	void Clear();
	amyCubeLing* GetCubeLing(){return m_CubeLing;}
	void SetAnnotaion(bool is);
	void SetView(amyUtil::ePlane p);
	void ReplaceCubeLing(amyCubeLing* cubeling);
private:
	amyCubeLing* m_CubeLing;
	amyAnnotationLing* m_Annotation;
	amyKeeper<amyCube>    m_Cube;

signals:
	void s_doubleclicked();
	//void s_dropped();
};

#endif // AMYDICOMCANVAS_H
