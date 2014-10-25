#pragma once
#include"VarMacro.h"
#include<string>
#include"amyTypes.h"
#include"amyKeeper.h"
using namespace std;

#define FETCH(type,obj,var) type& obj=(var)((type*)0) //调用重载的var括号运算符以转换类型


class amyVariableFactory;
class amyVariableManager;
class VAR_INTERFACE amyVariable
{
public:
	static amyVariable New(VTYPE type,string name);
	static amyVariable New(amyKeeper<void> keeper,VTYPE type,string name);
	amyVariable();
	amyVariable(VTYPE type,string name,amyKeeper<void> data);
	amyKeeper<void> Get(){return m_Ptr;}
	VTYPE GetType(){return m_Type;}
	string GetName(){return m_Name.GetPointer();}
	void  SetName(string name);
	template<typename T>
	amyKeeper<T> Get()
	{
		amyKeeper<T> m;
		m.Cast(m_Ptr);
		return m;
	}
	bool IsValid();
	template<typename T>
	T& operator()(T*)
	{
		T* a=(T*)m_Ptr.GetPointer();
		return *a;
	}
private:
	
	amyKeeper<char> m_Name;
	VTYPE  m_Type;
	amyKeeper<void>  m_Ptr;
	friend class amyVariableFactory;
	friend class amyVariableManager;

};

