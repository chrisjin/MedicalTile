#include"ClosingAndOpenning.h"
#include<string>
using namespace std;
#pragma once

class FillHoleForEverySlice:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "FillHoleForEverySlice";}
	virtual const char* GetCategory(){return "BasicFilters";}
	virtual void   Run();
};