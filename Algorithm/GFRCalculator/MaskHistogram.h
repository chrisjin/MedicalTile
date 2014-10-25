#pragma once
#include"amyAlgorithm.h"
class MaskHistogram:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "MaskHistogram";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual string      GetDescription()
	{
		return "You should put the images you want to calculate historgram for on the left and mask on the right";
	}
	//INPUT_NUM_SET(1)
	//OUTPUT_NUM_SET(1)
	virtual void   Run();
};

class OtsuMultiSeg:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "OtsuMultiSeg";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual string      GetDescription()
	{
		return "You should put the images you want to calculate historgram for on the left and mask on the right";
	}
	//INPUT_NUM_SET(1)
	//OUTPUT_NUM_SET(1)
	virtual void   Run();
};