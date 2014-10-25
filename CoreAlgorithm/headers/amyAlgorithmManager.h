#pragma once
#include"CoreAlgoMacro.h"
#include"amyPure.h"
#include<vector>
#include<QObject>
#include<QMap>
class QMenu;
class QTabWidget;
using namespace std;
class amyAlgorithm;
class COREALGO_INTERFACE amyAlgorithmQ:public QObject
{
	Q_OBJECT
public:
	amyAlgorithmQ(amyAlgorithm* alg):m_Algo(alg){}
	amyAlgorithm* GetAlgorithm(){return m_Algo;}
private:
	amyAlgorithm* m_Algo;
public slots:
	void Retrieve();
signals:
	void s_retrieve();
	void s_taskstart();
	void s_taskover();

};

class COREALGO_INTERFACE amyAlgorithmManager:public QObject
{
	Q_OBJECT
	DEFINE_SINGLETON(amyAlgorithmManager)
public:
	amyAlgorithmManager();
	void LoadAlgorithm();
	QMenu* GetAlgorithmMenu(QString cat,QWidget* parent=0);
	QTabWidget* GetAlgorithmTab(QWidget* parent=0);
	void ConnectRetrieveSignal(QObject* obj,const char* sig,amyAlgorithmQ* aq);
	amyAlgorithm* GetAlgorithmByName(QString name);
	void          GetAlgorithmsByCategory(QString cat,vector<amyAlgorithmQ*>& arr);
	void          GetAlgorithmsByCategory(QString cat,vector<amyAlgorithm*>& arr);
	void          GetCategoryList(vector<string>& arr);
public slots:
	void SendRetrieveSig();
signals:
	void s_algorithmchoose(amyAlgorithm*);
private:
	QMap<QString,amyAlgorithm*> m_Name2Algo;
	vector<amyAlgorithmQ*> m_AlgoArr;

};