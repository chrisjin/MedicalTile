#pragma once
#include"amyAlgorithm.h"
#include"GFRPanel.h"
#include"amyAlgorithmMessager.h"
#include<QIcon>
class GFRCalculator:public amyAlgorithm
{
public:
	virtual const char* GetAlgorithmName(){return "GFRCalculator";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual QFrame* CreatePanel(QWidget* parent){return new GFRPanel(this,parent);}
	virtual QIcon*  GetIcon(){return new QIcon(":/ICON/GFR");}
	//INPUT_NUM_SET(4)
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=3)
			goto BADEND;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			goto BADEND;
		if(arr[1].GetType()!=VTYPE_DATA_ARRAY||arr[2].GetType()!=VTYPE_DATA_ARRAY)
			goto BADEND;
GOODEND:
		return 1;
BADEND:
		this->PostError("Inputs should be <SSET> <DARR> <DARR>");
		return 0;
	}
	virtual void   Run();
};

class RegGFRCalculator:public GFRCalculator
{
public:
	virtual const char* GetAlgorithmName(){return "RegGFRCalculator";}
	virtual void   Run();
};

class TimePointArr:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "TimePointArr";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual QIcon*  GetIcon(){return new QIcon(":/ICON/TimePoint");}
	virtual void   Run();
};


class DrawSpecial:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=3)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		if(arr[1].GetType()!=VTYPE_DATA_ARRAY||arr[2].GetType()!=VTYPE_DATA_ARRAY)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "DrawSpecialCurve";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual void   Run();
};

DLL_DEFINE