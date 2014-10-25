#pragma once
#include"CoreAlgoMacro.h"
#include"amyAlgorithm.h"
class amyAlgorithmStack;
class COREALGO_INTERFACE amySubtractionAlgorithm:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=2)
			return 0;
		if(arr[0].GetType()!=VTYPE_CUBE)
			return 0;
		if(arr[1].GetType()!=VTYPE_CUBE)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "Subtraction";}
	virtual string      GetDescription();
	virtual string      GetHint();
	virtual void   Run();
};