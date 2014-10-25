#pragma once
#include"amyTypes.h"

#include"amyVariable.h"
#include"amyPure.h"
#include"AlgoMacro.h"
#include<vector>
using namespace std;
class amyAlgorithmStackPriavte;
class ALGOCRAFT_INTERFACE amyAlgorithmStack
{
	DEFINE_SINGLETON(amyAlgorithmStack)
public:
	amyAlgorithmStack();
	amyVariable Pop();
	amyVariable Top();
	void        Pop(vector<amyVariable>& arr,int num=1);
	void        Top(vector<amyVariable>& arr,int num=1);
	void        Top2Bottom(vector<amyVariable>& arr);
	void Push(const amyVariable& v);
	int GetSize();
	void Clear();
private:
	amyAlgorithmStackPriavte* _d;
	
};

class amyAlgorithmStatus
{
public:
	enum eStatus
	{
		STATUS_NORMAL,
		STATUS_ERROR,
		STATUS_NULL
	};
	static void SetStatus(eStatus st){m_Status=st;}
	static eStatus GetStatus(){return m_Status;}
private:
	static eStatus m_Status;
};