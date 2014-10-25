#pragma once
#include"ClosingAndOpenning.h"
class EdgePreserveSmooth:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "EdgePreserveSmooth";}
	virtual const char* GetCategory(){return "BasicFilters";}
	virtual void   Run();
};