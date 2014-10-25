#pragma once
#include<QScrollArea>
#include<vector>
#include<QPushButton>
class QIcon;
using namespace std;

class amyAlgorithmQ;
class amyAlgorithmScrollArea:public QScrollArea
{
	Q_OBJECT
public:
	amyAlgorithmScrollArea(QWidget* p=0);
	void SetAlgorithmArr(vector<amyAlgorithmQ*>& alarr);

private:
	vector<amyAlgorithmQ*> m_AlgoArr;
	QWidget* m_MainWidget;
};

class amyAlgorithmButton:public QPushButton
{
public:
	amyAlgorithmButton(amyAlgorithmQ* algo,QWidget* p=0);
	amyAlgorithmButton(QWidget* p=0);
private:
	amyAlgorithmQ* m_Algo;
	QIcon*         m_AlgoIcon;
};

class WidgetForOneAlgorithm:public QWidget
{
	Q_OBJECT
public:
	WidgetForOneAlgorithm(amyAlgorithmQ* algo,QWidget* p=0);
public slots:
	void ShowPanel();
private:
	amyAlgorithmQ*		  m_Algo;
	amyAlgorithmButton*   m_ApplyBtn;
	QPushButton*          m_PanelBtn;
	QFrame*               m_Panel;
};