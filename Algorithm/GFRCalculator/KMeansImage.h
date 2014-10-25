#include"PeakImage.h"

class KMeansImage:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "KMeansImage";}
	virtual const char* GetCategory(){return "Kidney";}
	virtual void   Run();
};