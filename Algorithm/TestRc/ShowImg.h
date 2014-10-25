#include"amyAlgorithm.h"
#include<QDialog>
#include"amyVariableView.h"
#include<QBoxLayout>
class Wraper:public QObject
{
	Q_OBJECT
public:
	
	Wraper()
	{
		//this->moveToThread(QCoreApplication::instance()->thread());
		
	}
	
	void func()
	{
		QDialog d;
		d.setLayout(new QVBoxLayout(&d));
		d.resize(100,400);
		d.layout()->addWidget(new amyVariableView);
		//amyDoubleThresholdWidget* w=new amyDoubleThresholdWidget(Qt::Vertical);
		//w->SetBound(0,40);
		//w->SetHighThreshold(35);
		//w->SetLowThreshold(30);
		//d.layout()->addWidget(w);
		d.exec();
	}
};

class ShowImg:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=0)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "ShowImg";}
	virtual const char* GetCategory(){return "Test";}
	virtual void   Run();
};

DLL_DEFINE