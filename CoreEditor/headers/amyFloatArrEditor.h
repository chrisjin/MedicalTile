//#pragma once
//#include"CoreEditorMacro.h"
//#include"amyVariableEditor.h"
//class QTableWidget;
//class amyFloatArr;
//class QPaintEvent;
//class QKeyEvent;
//class COREEDITOR_INTERFACE amyChartWidget:public QWidget,public amyInput<amyFloatArr*>
//{
//	Q_OBJECT
//public:
//	amyChartWidget(QWidget* parent=0);
//	void InitInput();
//	void paintEvent(QPaintEvent *dev);
//private:
//	float m_Max;
//	float m_Min;
//};
//class COREEDITOR_INTERFACE amyFloatArrEditor:public amyVariableEditor
//{
//public:
//	amyFloatArrEditor(QWidget *parent=0);
//	void InitInput(); 
//	void Confirm();
//	void keyTablePressEvent( QKeyEvent * event);
//	bool eventFilter(QObject *target, QEvent *event);
//	void Copy();
//	const char* GetName(){return "amyFloatArrEditor";}
//private:
//	QTableWidget* m_Table;
//	amyChartWidget* m_Chart;
//
//};