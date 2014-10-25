#include"amyAlgorithm.h"
class amyAlgorithmStack;
class amyAlgorithmStack;
class TDCalculator:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=2)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		if(arr[1].GetType()!=VTYPE_CUBE)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "TDCalculator";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual void   Run();
};

class AvgTDCalculator:public TDCalculator
{
public:
	virtual const char*  GetAlgorithmName(){return "AvgTDCalculator";}
	virtual const char*  GetCategory(){return "Kidney";}
	virtual void   Run();
};

class MaxTDCalculator:public TDCalculator
{
public:
	virtual const char*  GetAlgorithmName(){return "MaxTDCalculator";}
	virtual const char*  GetCategory(){return "Kidney";}
	virtual void   Run();
};
class ArrayCombine:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		for(int i=0;i<arr.size();i++)
		{
			if(arr[i].GetType()!=VTYPE_DATA_ARRAY)
				return 0;
		}
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "ArrayCombine";}
	virtual const char* GetCategory(){return "Statistics";}
	INPUT_NUM_FREE
	OUTPUT_NUM_SET(1)
	virtual void   Run();
private:
	int m_CubeNum;
	int m_SeriesNum;
};

class CircleGen:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=0)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "CircleGen";}
	virtual const char* GetCategory(){return "Statistics";}
	virtual void   Run();
private:
};
DLL_DEFINE