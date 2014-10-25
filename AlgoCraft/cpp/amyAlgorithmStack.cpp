#include"amyAlgorithmStack.h"
#include<deque>
using namespace std;
IMPLEMENT_SINGLETON(amyAlgorithmStack)
class amyAlgorithmStackPriavte
{
public:
	deque<amyVariable> m_Stack;
};
amyAlgorithmStack::amyAlgorithmStack()
{
	_d=new amyAlgorithmStackPriavte;
}
amyVariable amyAlgorithmStack::Pop()
{
	amyVariable v;
	if(this->_d->m_Stack.size()>0)
	{
		v= this->Top();
		this->_d->m_Stack.pop_back();
	}
	return v;
}
void amyAlgorithmStack::Pop(vector<amyVariable>& arr,int num)
{
	for(int i=0;i<num;i++)
	{
		if(this->GetSize()==0)
			break;
		arr.push_back(this->Pop());
	}
}
void amyAlgorithmStack::Top(vector<amyVariable>& arr,int num)
{
	deque<amyVariable>::reverse_iterator ritr=_d->m_Stack.rbegin();
	for(;ritr!=_d->m_Stack.rend();ritr++)
	{
		arr.push_back(*ritr);
		if(arr.size()==num)
			break;
	}
}
void amyAlgorithmStack::Top2Bottom(vector<amyVariable>& arr)
{
	deque<amyVariable>::reverse_iterator ritr=_d->m_Stack.rbegin();
	for(;ritr!=_d->m_Stack.rend();ritr++)
	{
		arr.push_back(*ritr);
	}
}
void amyAlgorithmStack::Push(const amyVariable& v)
{
	
	this->_d->m_Stack.push_back(v);
}

amyVariable amyAlgorithmStack::Top()
{
	amyVariable v;
	if(this->_d->m_Stack.size()>0)
	{
		v= this->_d->m_Stack[this->_d->m_Stack.size()-1];
	}
	return v;
}
int amyAlgorithmStack::GetSize()
{
	return _d->m_Stack.size();
}
void amyAlgorithmStack::Clear()
{
	while(1)
	{
		if(this->_d->m_Stack.size()==0)
			break;
		this->_d->m_Stack.pop_back();
	}
}