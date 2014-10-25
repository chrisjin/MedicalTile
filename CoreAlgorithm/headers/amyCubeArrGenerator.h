#pragma once
#include"CoreAlgoMacro.h"
#include"amyAlgorithm.h"
class amyAlgorithmBridge;
class COREALGO_INTERFACE amyCubeArrGenerator:public amyAlgorithm
{
public:
	//INPUT_NUM_SET(1)
 //   OUTPUT_NUM_SET(0);
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=1)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		return 1;
	}
	virtual  const char* GetCategory()
	{
		return "Generator";
	}
	virtual const char* GetAlgorithmName(){return "CubeArrGenerator";}
	//virtual bool CheckArgumetType(int index,VTYPE t)
	//{
	//	return t==VTYPE_SERIES_SET?1:0;
	//}
	virtual void   Run();
};