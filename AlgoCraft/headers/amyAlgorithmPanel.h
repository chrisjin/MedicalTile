#pragma once
#include"AlgoMacro.h"
#include<QFrame>
#include<QString>
class QWidget;
class QIcon;
class amyAlgorithm;
class QTreeWidget;
class ALGOCRAFT_INTERFACE amyAlgorithmPanel:public QFrame
{
	Q_OBJECT
public:
	amyAlgorithmPanel(amyAlgorithm* a,QWidget* p);
	void           Initialize(amyAlgorithm* a);
	amyAlgorithm*  GetAlgorithm();
	void           addPanel(QString name,QWidget* w);
protected:
	void focusOutEvent ( QFocusEvent * event );
	void hideEvent(QHideEvent *);
signals:
	void s_focusout();
private:
	amyAlgorithm*	 m_Algo;
	QTreeWidget*     m_TreeWidget;
};