#include"amyAlgorithm.h"

class Test:public amyAlgorithm
{
public:
	bool CheckInputArr(vector<amyVariable>& arr)
	{
		if(arr.size()!=2)
			return 0;
		if(arr[0].GetType()!=VTYPE_CUBE)
			return 0;
		return 1;
	}
	virtual const char* GetCategory(){return "new";}
	virtual const char* GetAlgorithmName(){return "KKK";}
	virtual void   Run();
};