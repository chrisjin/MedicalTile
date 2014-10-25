#include"amyAlgorithm.h"
#include<vector>
#include<string>
#include<QString>
#include"CoreAlgoMacro.h"
using namespace std;
////// 务必在其他插件载入之后再载入
class amyAlgorithmManager;
class COREALGO_INTERFACE amyXMLAlgorithm:public amyAlgorithm   
{
public:
	bool CheckInputArr(vector<amyVariable>& arr);
	virtual const char* GetAlgorithmName();
	virtual const char* GetCategory(){return m_Category.c_str();}
	virtual void   Run();
	bool         LoadXML(QString filename,amyAlgorithmManager* am);
private:
	vector<amyAlgorithm*> m_AlgorithmArr;
	string m_Name;
	string m_Category;
};