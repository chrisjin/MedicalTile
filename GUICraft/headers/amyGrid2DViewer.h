#pragma once 
#include"GuiMacro.h"
#include<QWidget>
class amyDICOMCanvas;
class QGridLayout;
#include<vector>
using namespace std;
class GUI_INTERFACE amyGrid2DViewer:public QWidget
{
	Q_OBJECT
public:
	amyGrid2DViewer(QWidget* p=0);
	int GetMeasureMode();
	enum eLayout
	{
		LAYOUT_1X1,
		LAYOUT_2X2,
		LAYOUT_3X3
	};
private:
	bool m_IsSamize;
	vector<amyDICOMCanvas*> m_CanvasArr;
	amyDICOMCanvas  *m_ActivatedCanvas;
	QGridLayout *m_CanvasLayout;
	eLayout     m_LayoutType;
	
public slots:
	void Set1X1();
	void Set2X2();
	void Set3X3();
	void SamizeSlice(int);
	void SamizeZoom(int);
	void SamizeTranslate(QPoint);
	void SetSamize();
	void SwitchMeasurementMode();
	void DeleteMeasurement();
	void ShowAnnotaion();
	void Maximize();
};