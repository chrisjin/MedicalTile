#pragma once
#include"amyAlgorithm.h"
class CurveSmooth:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=1)
			return 0;
		if(arr[0].GetType()!=VTYPE_DATA_ARRAY)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "CurveSmooth";}
	virtual const char* GetCategory(){return "Kidney";}
	//INPUT_NUM_SET(1)
	//OUTPUT_NUM_SET(1)
	virtual void   Run();
};


class CurveDiff:public CurveSmooth
{
public:
	virtual const char* GetAlgorithmName(){return "CurveDiff";}
	virtual void   Run();
};