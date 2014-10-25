#include"ClosingAndOpenning.h"
#include<string>
using namespace std;
class LargestComponent:public BasicFilter
{
public:
	virtual const char* GetAlgorithmName(){return "LargestComponent";}
	virtual const char* GetCategory(){return "BasicFilters";}
	virtual void   Run();
};