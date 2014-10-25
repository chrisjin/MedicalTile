#pragma once
#include"amyAlgorithm.h"
#include<QObject>
#include"amyVariable.h"
#include<vector>
#include<string>
using namespace std;
class ALGOCRAFT_INTERFACE amyAlgorithmRunner:public QObject
{

	Q_OBJECT
	DEFINE_SINGLETON(amyAlgorithmRunner)	
public:
	bool Start(amyAlgorithm* algo,
		vector<amyVariable>& inputs,vector<amyVariable>& outputs);
	bool Start(amyAlgorithm* algo);
	//bool Start(amyAlgorithm* algo,vector<amyVariable>& outputs);
private:
	bool CheckInput(amyAlgorithm* algo,vector<amyVariable>& inputs);
	bool Run(amyAlgorithm* algo);
signals:
	void s_begin_check();
	void s_end_check();
	void s_begin_run();
	void s_end_run();
};