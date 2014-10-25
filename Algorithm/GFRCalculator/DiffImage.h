#pragma once
#include"PeakImage.h"

class DiffImage:public CubeTimeSequence
{
public:
	virtual const char* GetAlgorithmName(){return "DiffImage";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual float  ForVoxTimeSequence(vector<int>& arr);
};