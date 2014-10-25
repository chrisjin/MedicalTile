#ifndef QAMYCUISINEWINDOW_H
#define QAMYCUISINEWINDOW_H

#include <QMainWindow>
#include"amyVariable.h"
#include "ui_QAMYCuisineWindow.h"
class amyVariableArea;
class amyVariableView;
class amyAlgorithm;
class QLabel;
class QTabWidget;
class QProgressBar;
class amyAlgorithmRunner;
class QAMYCuisineWindow : public QMainWindow
{
	Q_OBJECT

public:
	QAMYCuisineWindow(QWidget *parent = 0);
	~QAMYCuisineWindow();
	void mouseVariableAreaDoubleClickEvent(QMouseEvent * event);
	void contextVariableAreaMenuEvent(QContextMenuEvent *);
	void EditVariable(amyVariable& v);
	bool eventFilter(QObject *target, QEvent *event);
	void closeEvent(QCloseEvent *event);
public slots:
	//void ContextVariableViewMenu(QPoint p);

	void ApplyAlgorithm(amyAlgorithm* algo);
	void SerializeSelected();
	void DeseraializeSelected();
	void BeginProgress();
	void EndProgress();
	void StepProgress(int);
	
	//void InvalidInputNum();
	//void InvalidInputType();
	//void InvalidOutputNum();
	void InputCheckingBegin();
	void InputCheckingEnd();
	void AlgorithmBegin();
	void AlgorithmEnd();
private:
	Ui::QAMYCuisineWindow ui;
	amyVariableView*	m_VariableArea;
	QTabWidget*			m_AlgoTab;
	QPoint				m_ContextMenuPos;
	QLabel*			    m_StatusMessage;
	QProgressBar*		m_ProgressBar;
};

#endif // QAMYCUISINEWINDOW_H
