#pragma once
#include"AlgoMacro.h"
#include<string>
#include"amyPure.h"
#include<map>
#include<string>
#include<vector>
using namespace std;
class amyAlgorithm;
class ALGOCRAFT_INTERFACE amyAlgorithmMessager
{
	DEFINE_SINGLETON(amyAlgorithmMessager)
public:
	void PostWarning(amyAlgorithm* algo,string str);
	void PostError  (amyAlgorithm* algo,string str);
	void ClearAll();
	void GetWarningSrcArr(vector<amyAlgorithm*>& algo);
	void GetErrorSrcArr(vector<amyAlgorithm*>& algo);

	void GetWarningArr(amyAlgorithm* algo,vector<string>& arr);
	void GetErrorArr(amyAlgorithm* algo,vector<string>& arr);

	void ShowAndClearAll();
	bool HasError();
	bool HasWarning();
private:
	string ToString();
private:
	typedef map<amyAlgorithm*,vector<string>>::iterator tIterator;
	map<amyAlgorithm*,vector<string>> m_Algo2Warnings;
	map<amyAlgorithm*,vector<string>> m_Algo2Errors;
};