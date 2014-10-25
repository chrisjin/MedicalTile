#pragma once
#include"amyDICOMCanvas.h"
class amySelectionLing;
class amyAdvDICOMCanvas:public amyDICOMCanvas
{
	Q_OBJECT
public:
	amyAdvDICOMCanvas(QWidget *parent=0);
	void UpdateViewSelectionLing();
	void HideViewSelectionLing();
	void ShowViewSelectionLing();
	void SetViewSelectionLing(amyUtil::ePlane p);
	void resizeEvent(QResizeEvent*);

	virtual bool OnAcceptSeries(amyKeeper<amySeries> k);
	virtual bool OnAcceptCube(amyKeeper<amyCube> k);
private:
	amySelectionLing*  m_AxialViewSelection; 
	amySelectionLing*  m_CoronalViewSelection; 
	amySelectionLing*  m_SagittalViewSelection; 
public slots:
	void SelectView();
	//void UpdateAnnotation();
	//void SliceChanged(int s);
};