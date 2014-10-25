#ifndef QAMYWINDOW_H
#define QAMYWINDOW_H

#include <QMainWindow>
#include "ui_QAMYWindow.h"
#include <QTableView>
#include "amyFolderView.h"
class amyPatientModel;
class amyCanvas;
class amyDICOMCanvas;
class QToolButton;
class QGridLayout;
class amyGrid2DViewer;
class QStackedWidget;
class amyMPRViewer;
class QAMYWindow : public QMainWindow
{
	Q_OBJECT

public:
	//enum eLayout
	//{
	//	LAYOUT_1X1,
	//	LAYOUT_2X2,
	//	LAYOUT_3X3
	//};
	QAMYWindow(QWidget *parent = 0);
	~QAMYWindow();
	void closeEvent(QCloseEvent *event);
	//amyDICOMCanvas  *GetActivatedCanvas(){return m_ActivatedCanvas;}
private:
	Ui::QAMYWindow ui;
	//eLayout     m_LayoutType;
	QToolButton *m_FolderOpenButton; 
	QToolButton *m_CanvasLayoutButton;
	QToolButton *m_ChainButton;
	QToolButton* m_MeasurementButton;
	//QGridLayout *m_CanvasLayout;
	amyFolderView  *m_FolderView;
	//amyDICOMCanvas  *m_ActivatedCanvas;
	//vector<amyDICOMCanvas*> m_CanvasArr;
	amyGrid2DViewer *m_2DViewer;
	amyMPRViewer    *m_MPRViewer;
	QStackedWidget  *m_ViewerContainer;
	bool m_IsSamize;
public slots:
	//void SamizeSlice(int);
	void SetSamize();
	//void SamizeZoom(int);
	//void SamizeTranslate(QPoint);
	void SwitchMeasurementMode();
	//void DeleteMeasurement();
	//void ShowAnnotaion();
	void OpenFolder();
	//void Maximize();
	void Set2D();
	//void Set2X2();
	//void Set3X3();
	void Set3DAndMPR();
	
};
class Test
{
};
#endif // QAMYWINDOW_H
