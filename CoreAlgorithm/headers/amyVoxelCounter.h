#pragma once
#include"CoreAlgoMacro.h"
#include"amyAlgorithm.h"

class COREALGO_INTERFACE amyVoxelCounter:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "VoxelCounter";}
	virtual void   Run();

};

class COREALGO_INTERFACE amyVolumeCounter:public amyAlgorithm
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
	virtual const char* GetCategory()
	{
		return "Algorithm";
	}
	virtual const char* GetAlgorithmName(){return "VolumeCounter";}
	virtual void   Run();
};