#include"amyAlgorithm.h"

class GFRPlot:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=3)
			return 0;
		if(arr[0].GetType()!=VTYPE_SERIES_SET)
			return 0;
		if(arr[1].GetType()!=VTYPE_CUBE||arr[2].GetType()!=VTYPE_CUBE)
			return 0;
		return 1;
	}
	virtual const char* GetAlgorithmName(){return "GFRPlot";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual string      GetDescription(){return "You should choose a <b>sst</b> for all series, a <b>cube</b> for whole kidney and a <b>cube</b> for cortex.";}
	virtual void   Run();


};