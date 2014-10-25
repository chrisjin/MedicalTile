#pragma once
#include"GuiMacro.h"
#include<QWidget>
class amyDICOMCanvas;
class amyMPRLineCubeLing;
class amy3DViewer;
class GUI_INTERFACE amyMPRViewer:public QWidget
{
	Q_OBJECT
public:
	amyMPRViewer(QWidget* p=0);
public slots:
	void OnDrop();
	void AxialHorizontal(int);
	void AxialVertical(int);
	void CoronalHorizontal(int);
	void CoronalVertical(int);
	void SagittalHorizontal(int);
	void SagittalVertical(int);

	void CoronalSliceChange(int);
	void AxialSliceChange(int);
	void SagittalSliceChange(int);

	//void AxialLineChanged(int);
	//void CoronalLineChanged(int);
	//void SaggitalLineChanged(int);
private:
	amyDICOMCanvas* m_AxialViewer;
	amyDICOMCanvas* m_CoronalViewer;
	amyDICOMCanvas* m_SagittalViewer;

	amyMPRLineCubeLing* m_AxialLing;
	amyMPRLineCubeLing* m_CoronalLing;
	amyMPRLineCubeLing* m_SagittalLing;

	amy3DViewer* m_3DViewer;
	//int m_AxialSlicePos;
	//int m_AxialLinePos;

	//int m_CoronalSlicePos;
	//int m_CoronalLinePos;

	//int m_SagittalSlicePos;
	//int m_SagittalLinePos;


};	