#pragma once
#include"amyAlgorithm.h"
class amyAlgorithmStack;
class amyDLLSubtractionAlgorithm:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=1)
			return 0;
		if(arr[0].GetType()!=VTYPE_CUBE)
			return 0;
		return 1;
	}
	virtual  const char* GetAlgorithmName(){return "DllSubtraction";}
	virtual void   Run();
};
DLL_DEFINE
