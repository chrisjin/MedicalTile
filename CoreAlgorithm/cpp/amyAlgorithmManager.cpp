#include"amyAlgorithmManager.h"
#include<QMenu>
#include"amyAlgorithm.h"
#include"amySubtractionAlgorithm.h"
#include"amyAlgorithmStack.h"
#include"amyThresholdAlgorithm.h"
#include"amyMaskGenerator.h"
#include<QLibrary>
#include<QDir>
#include<qDebug>
#include<QApplication>
#include"amySplashScreen.h"
#include"amyXMLAlgorithm.h"
#include"amyCubeArrGenerator.h"
#include<set>
#include"amyVoxelCounter.h"
#include"amyAlgorithmBridge.h"
#include<QToolBox>
#include<QTabWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QScrollArea>
#include"amyAlgorithmScrollArea.h"
#include"amyCubeAND.h"
IMPLEMENT_SINGLETON(amyAlgorithmManager)
void amyAlgorithmQ::Retrieve()
{
	emit s_retrieve();
}
amyAlgorithmManager::amyAlgorithmManager()
{
	//LoadAlgorithm();
}
typedef amyAlgorithm* (*LibFunc)(int index);
typedef int           (*NumFunc)();
void amyAlgorithmManager::LoadAlgorithm()
{
	amyAlgorithm* a;
	a=new amySubtractionAlgorithm;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	a=new amyThresholdAlgorithm;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	//a=new amyMaskGenerator;
	//m_AlgoArr.push_back(new amyAlgorithmQ(a));
	//m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	a=new amyCubeArrGenerator;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	a=new amyVoxelCounter;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	a=new amyVolumeCounter;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);

	a=new amyCubeAND;
	m_AlgoArr.push_back(new amyAlgorithmQ(a));
	m_Name2Algo.insert(QString::fromLocal8Bit(a->GetAlgorithmName()),a);
	
	QDir dir;  
	qDebug()<<QDir::currentPath();
	dir.setPath("./Algorithm");
	QStringList filter;
    filter<<"*.dll";
    dir.setNameFilters(filter);
	if(dir.exists())
	{
		dir.setFilter(QDir::Files | QDir::NoSymLinks);
		QFileInfoList infolist = dir.entryInfoList (QDir::Files | QDir::NoDotAndDotDot);
		QFileInfoList::Iterator itr=infolist.begin();
		for(;itr!=infolist.end();itr++)
		{
			QLibrary dll(itr->absoluteFilePath());
			dll.load();
			if(dll.isLoaded())
			{
				LibFunc func=(LibFunc)dll.resolve("GetAlgorithmByIndex");
				NumFunc funcnum=(NumFunc)dll.resolve("GetAlgorithmNum");
				if(func&&funcnum)
				{
					int num=funcnum();
					for(int i=0;i<num;i++)
					{
						amyAlgorithm* al=func(i);
						if(al)
						{
							amySplashScreen *ss=amySplashScreen::GetInstance();
							ss->showMessage(QString("Loading: ")+al->GetAlgorithmName(),Qt::AlignCenter);
							m_AlgoArr.push_back(new amyAlgorithmQ(al));
							QString name=QString::fromLocal8Bit(al->GetAlgorithmName());
							m_Name2Algo.insert(name,al);
						}
					}
				}
			}
		}
	}
	QDir ForXML;
	dir.setPath("./Algorithm");
	QStringList forxmlfilter;
	forxmlfilter<<"*.algo";
	dir.setNameFilters(forxmlfilter);
	if(dir.exists())
	{
		dir.setFilter(QDir::Files | QDir::NoSymLinks);
		QFileInfoList infolist = dir.entryInfoList (QDir::Files | QDir::NoDotAndDotDot);
		QFileInfoList::Iterator itr=infolist.begin();
		for(;itr!=infolist.end();itr++)
		{
			amyXMLAlgorithm* al=new amyXMLAlgorithm;
			int flag=al->LoadXML(itr->absoluteFilePath(),this);
			if(flag)
			{
				amySplashScreen::GetInstance()->showMessage(QString("Loading: ")+al->GetAlgorithmName(),Qt::AlignCenter);
				m_AlgoArr.push_back(new amyAlgorithmQ(al));
				m_Name2Algo.insert(QString::fromLocal8Bit(al->GetAlgorithmName()).toLower(),al);
			}
		}
	}
	//QLibrary dll("./Algorithm/ROISegmentation.dll");
	//dll.load();
	//if(dll.isLoaded())
	//{
	//	LibFunc func=(LibFunc)dll.resolve("GetAlgorithm");
	//	if(func)
	//	{
	//		amyAlgorithm* al=func(amyAlgorithmStack::GetInstance());
	//		m_AlgoArr.push_back(new amyAlgorithmQ(al));
	//	}
	//}


}
void amyAlgorithmManager::ConnectRetrieveSignal(QObject* obj,const char* sig,amyAlgorithmQ* aq)
{
	connect(obj,sig,aq,SIGNAL(s_retrieve()));
	connect(aq,SIGNAL(s_retrieve()),this,SLOT(SendRetrieveSig()),Qt::UniqueConnection);
}
QMenu* amyAlgorithmManager::GetAlgorithmMenu(QString cat,QWidget* o)
{
	vector<amyAlgorithmQ*> alist;
	GetAlgorithmsByCategory(cat,alist);
	QMenu* menu=new QMenu(cat,o);
	for(int i=0;i<alist.size();i++)
	{
		amyAlgorithm* algo=alist[i]->GetAlgorithm();
		QAction* action=new QAction(algo->GetAlgorithmName(),o);
		menu->addAction(action);
		ConnectRetrieveSignal(action,SIGNAL(triggered()),alist[i]);
		//connect(action,SIGNAL(triggered()),m_AlgoArr[i],SIGNAL(s_retrieve()));
		//connect(m_AlgoArr[i],SIGNAL(s_retrieve()),this,SLOT(SendRetrieveSig()));
	}
	return menu;
}
QTabWidget* amyAlgorithmManager::GetAlgorithmTab(QWidget* parent)
{
	QTabWidget* tab=new QTabWidget(parent);
	vector<string> catarr;
	this->GetCategoryList(catarr);
	tab->setTabPosition(QTabWidget::West);
	for(int i=0;i<catarr.size();i++)
	{	
		vector<amyAlgorithmQ*> algoarr;
		this->GetAlgorithmsByCategory(catarr[i].c_str(),algoarr);
		amyAlgorithmScrollArea* sa=new amyAlgorithmScrollArea(parent);
		sa->SetAlgorithmArr(algoarr);
		tab->addTab(sa,catarr[i].c_str());
	}
	
	return tab;
}
void amyAlgorithmManager::SendRetrieveSig()
{
	amyAlgorithmQ* aq=qobject_cast<amyAlgorithmQ*>(this->sender());
	if(aq)
	emit s_algorithmchoose(aq->GetAlgorithm());
}

amyAlgorithm* amyAlgorithmManager::GetAlgorithmByName(QString name)
{
	if(m_Name2Algo.contains(name))
	{
		return m_Name2Algo[name];
	}
	else
	{
		return 0;
	}
}

void amyAlgorithmManager::GetAlgorithmsByCategory(QString cat,vector<amyAlgorithmQ*>& arr)
{
	for(int i=0;i<m_AlgoArr.size();i++)
	{
		if(cat==m_AlgoArr[i]->GetAlgorithm()->GetCategory())
		{
			arr.push_back(m_AlgoArr[i]);
		}
	}
}
void amyAlgorithmManager::GetAlgorithmsByCategory(QString cat,vector<amyAlgorithm*>& arr)
{
	for(int i=0;i<m_AlgoArr.size();i++)
	{
		if(cat==m_AlgoArr[i]->GetAlgorithm()->GetCategory())
		{
			arr.push_back(m_AlgoArr[i]->GetAlgorithm());
		}
	}
}

void amyAlgorithmManager::GetCategoryList(vector<string>& arr)
{
	set<string> cats;
	for(int i=0;i<m_AlgoArr.size();i++)
	{
		if(cats.find(m_AlgoArr[i]->GetAlgorithm()->GetCategory())==cats.end())
		{
			string c=m_AlgoArr[i]->GetAlgorithm()->GetCategory();
			cats.insert(c);
			arr.push_back(m_AlgoArr[i]->GetAlgorithm()->GetCategory());
		}
	}
}