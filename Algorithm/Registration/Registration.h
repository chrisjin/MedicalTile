#include"amyAlgorithm.h"

class Registration:public amyAlgorithm
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
	virtual const char* GetAlgorithmName(){return "Registration";}
	virtual void   Run();
};
DLL_DEFINE