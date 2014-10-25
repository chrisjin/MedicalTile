#include"amyAlgorithmMessager.h"
#include"amyAlgorithm.h"
#include<QMessageBox>
#include<sstream>
using namespace std;
IMPLEMENT_SINGLETON(amyAlgorithmMessager)

#define MESSAGEBOX(str) QMessageBox::information(0,"I TELL YOU",str)
void amyAlgorithmMessager::PostWarning(amyAlgorithm* algo,string str)
{
	m_Algo2Warnings[algo].push_back(str);
}
void amyAlgorithmMessager::PostError  (amyAlgorithm* algo,string str)
{
	m_Algo2Errors[algo].push_back(str);
}
void amyAlgorithmMessager::ClearAll()
{
	m_Algo2Warnings.clear();
	m_Algo2Errors.clear();
}
void amyAlgorithmMessager::GetWarningSrcArr(vector<amyAlgorithm*>& algo)
{
	tIterator itr=m_Algo2Warnings.begin();
	for(;itr!=m_Algo2Warnings.end();itr++)
	{
		algo.push_back(itr->first);
	}
}
void amyAlgorithmMessager::GetErrorSrcArr(vector<amyAlgorithm*>& algo)
{
	tIterator itr=m_Algo2Errors.begin();
	for(;itr!=m_Algo2Warnings.end();itr++)
	{
		algo.push_back(itr->first);
	}
}

void amyAlgorithmMessager::GetWarningArr(amyAlgorithm* algo,vector<string>& arr)
{
	tIterator itr=m_Algo2Warnings.find(algo);
	if(m_Algo2Warnings.end()==itr)
		return;
	arr=m_Algo2Warnings[algo];
}
void amyAlgorithmMessager::GetErrorArr(amyAlgorithm* algo,vector<string>& arr)
{
	tIterator itr=m_Algo2Errors.find(algo);
	if(m_Algo2Errors.end()==itr)
		return;
	arr=m_Algo2Errors[algo];
}

string amyAlgorithmMessager::ToString()
{
	string ret;

	tIterator eitr=m_Algo2Errors.begin();
	for(;eitr!=m_Algo2Errors.end();eitr++)
	{
		ret+="ERRORS From ";
		ret+=eitr->first->GetAlgorithmName();
		ret+=":\n";
		vector<string>& earr=eitr->second;
		for(int i=0;i<earr.size();i++)
		{
			//stringstream ss;
			//ss<<i+1;
			ret+="--";
			//ret+=ss.str();
			ret+=" ";
			ret+=earr[i];
			ret+="\n";
		}
	}

	tIterator witr=m_Algo2Warnings.begin();
	for(;witr!=m_Algo2Warnings.end();witr++)
	{
		ret+="Warnings From ";
		ret+=witr->first->GetAlgorithmName();
		ret+=":\n";
		vector<string>& warr=witr->second;
		for(int i=0;i<warr.size();i++)
		{
			//stringstream ss;
			//ss<<i+1;
			ret+="--";
			//ret+=ss.str();
			ret+=" ";
			ret+=warr[i];
			ret+="\n";
		}
	}
	return ret;
}
void amyAlgorithmMessager::ShowAndClearAll()
{
	MESSAGEBOX(ToString().c_str());
	ClearAll();
}
bool amyAlgorithmMessager::HasError()
{
	if(m_Algo2Errors.size()!=0)
		return 1;
	else
		return 0;
}
bool amyAlgorithmMessager::HasWarning()
{
	if(m_Algo2Warnings.size()!=0)
		return 1;
	else
		return 0;
}