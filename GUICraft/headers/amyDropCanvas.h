#pragma once
#include"GuiMacro.h"
#include"amyCanvas.h"
#include"amyVariable.h"
class amySeries;
class amyCube;
class GUI_INTERFACE amyDropCanvas:public amyCanvas
{
	Q_OBJECT
public:
	amyDropCanvas(QWidget* p=0);
	virtual void dropEvent(QDropEvent *event);
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual bool IsAccept(VTYPE t);
	virtual bool OnAcceptSeries(amyKeeper<amySeries> k);
	virtual bool OnAcceptCube(amyKeeper<amyCube> k);
signals:
	void s_dropped();
};