#pragma once
#include"amyAlgorithm.h"
#include"amyCube.h"
class CubeTimeSequence:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=1)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		return 1;
	}
	virtual void   Run();
	virtual float  ForVoxTimeSequence(vector<int>& arr)=0;
	virtual amyCube::tCube::Pointer PreprocessCube(amyCube::tCube::Pointer);
};
class PeakImage:public CubeTimeSequence
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=1)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "PeakImage";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual float  ForVoxTimeSequence(vector<int>& arr);
};

class PeakMulTimeImage:public PeakImage
{
public:
	virtual const char* GetAlgorithmName(){return "PeakMulTimeImage";}
	virtual float  ForVoxTimeSequence(vector<int>& arr);
};
//class PeakImageWithFactors:public PeakImage
//{
//public:
//	virtual const char* GetAlgorithmName(){return "PeakImageWithFactors";}
//	virtual amyCube::tCube::Pointer PreprocessCube(amyCube::tCube::Pointer);
//};

class HalfPeakImage:public PeakImage
{
public:
	virtual const char* GetAlgorithmName(){return "HalfPeakImage";}
	virtual float  ForVoxTimeSequence(vector<int>& arr);
};

class SumImage:public PeakImage
{
public:
	virtual const char* GetAlgorithmName(){return "SumImage";}
	virtual float  ForVoxTimeSequence(vector<int>& arr);

};