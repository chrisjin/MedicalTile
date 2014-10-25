//#pragma once
//#include"CoreEditorMacro.h"
//#include"amyVariableEditor.h"
//#include<QWidget>
//#include"amyCanvas.h"
//class amyPointArr;
//class QTableWidget;
//class amyChartLing;
//class COREEDITOR_INTERFACE amyChartXYWidget:public amyCanvas,public amyInput<amyPointArr*>
//{
//	Q_OBJECT
//public:
//	amyChartXYWidget(QWidget* parent=0);
//	void InitInput();
//	//void paintEvent(QPaintEvent *dev);
//private:
//	amyChartLing *m_ChartLing;
//	float m_XMax;
//	float m_XMin;
//	float m_YMax;
//	float m_YMin;
//};
//
//class COREEDITOR_INTERFACE amyPointArrEditor:public amyVariableEditor
//{
//public:
//	amyPointArrEditor(QWidget *parent=0);
//	void InitInput(); 
//	void Confirm();
//	void keyTablePressEvent( QKeyEvent * event);
//	bool eventFilter(QObject *target, QEvent *event);
//	void Copy();
//	const char* GetName(){return "amyPointArrEditor";}
//private:
//	QTableWidget* m_Table;
//	amyChartXYWidget* m_Chart;
//
//};