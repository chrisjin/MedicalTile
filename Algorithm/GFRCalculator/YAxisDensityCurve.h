#pragma once
#include"amyAlgorithm.h"

class YAxisDensityCurve:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "YAxisDensityCurve";}
	virtual const char* GetCategory(){return "Kidney";}
	//virtual QIcon*  GetIcon(){return new QIcon(":/ICON/TimePoint");}
	virtual bool   CheckArgumetType(int index,VTYPE t)
	{
		if(t==VTYPE_CUBE)
			return 1;
		else
			return 0;
	}
	INPUT_NUM_SET(2)
	OUTPUT_NUM_SET(1)
	virtual void   Run();
};