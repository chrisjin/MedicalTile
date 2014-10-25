#include"amyAlgorithmRunner.h"
#include"amyAlgorithmStack.h"
#include"amyAlgorithm.h"
#include"amyAlgorithmMessager.h"
#include<QMessageBox>
IMPLEMENT_SINGLETON(amyAlgorithmRunner)




bool amyAlgorithmRunner::CheckInput(amyAlgorithm* algo,vector<amyVariable>& inputs)
{
	bool ret=1;
	emit s_begin_check();
	amyAlgorithmMessager* am=amyAlgorithmMessager::GetInstance();
	if(!algo->CheckInputArr(inputs))
	{
		am->PostError(algo,"Invalid Input");
		ret=0;
	}
	emit s_end_check();
	return ret;
}
bool amyAlgorithmRunner::Run(amyAlgorithm* algo)
{
	emit s_begin_run();
	algo->Run();
	emit s_end_run();
	if(amyAlgorithmMessager::GetInstance()->HasError())
		return 0;
	else 
		return 1;
}
bool amyAlgorithmRunner::Start(amyAlgorithm* algo)
{
	vector<amyVariable> inputarr;
	amyAlgorithmStack* as=amyAlgorithmStack::GetInstance();
	as->Top2Bottom(inputarr);

	if(0==CheckInput(algo,inputarr))
		return 0;
	if(0==Run(algo))
		return 0;
	
	return 1;
}
//bool amyAlgorithmRunner::Start(amyAlgorithm* algo,vector<amyVariable>& outputs)
//{
//
//}
bool amyAlgorithmRunner::Start(amyAlgorithm* algo,
	vector<amyVariable>& inputs,vector<amyVariable>& outputs)
{
	bool check_flag=CheckInput(algo,inputs);
	if(check_flag==0)
		return 0;

	amyAlgorithmStack* as=amyAlgorithmStack::GetInstance();
	int stacksize=as->GetSize();
	for(int i=inputs.size()-1;i>=0;i--)
	{
		as->Push(inputs[i]);
	};

	if(0==Run(algo))
		return 0;
	while(1)
	{
		if(as->GetSize()==stacksize)
			break;
		amyVariable v=as->Pop();
		outputs.push_back(v);
	}
	std::reverse(outputs.begin(),outputs.end());
	return 1;
}