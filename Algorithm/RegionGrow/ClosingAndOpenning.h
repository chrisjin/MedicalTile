#pragma once
#include"amyAlgorithm.h"
#include<string>
using namespace std;
class BasicFilter:public amyAlgorithm
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
	virtual string      GetDescription();
	virtual const char* GetCategory(){return "BasicFilters";}
	//OUTPUT_NUM_SET(1)
	//INPUT_NUM_SET(1)
};

class Opening:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "Opening";}
	virtual void   Run();
};


class Closing:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "Closing";}
	virtual void   Run();
};

class Gaussian:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "Gaussian";}
	virtual void   Run();
};

class Erode:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "Erode";}
	virtual void   Run();
};