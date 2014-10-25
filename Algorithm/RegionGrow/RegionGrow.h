#pragma once
#include"ClosingAndOpenning.h"

class ThresholdDIY:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "CustomThreshold";}
	virtual void   Run();
};
DLL_DEFINE