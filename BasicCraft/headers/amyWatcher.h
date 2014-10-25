#pragma once
#include"BasicMacro.h"
#include"amyKeeper.h"
template<typename T> 
class BASICCRAFT_TEMPLATE_INTERFACE amyWatcher
{
public:
	amyWatcher(amyKeeper<T>& keeper)
	{
		m_Destructor=keeper.m_Destructor;
		m_DestructFunc=keeper.m_DestructFunc;
		m_Counter=keeper.m_Counter;
		IncWatcher();
	}
	amyWatcher(const amyWatcher& watcher)
	{
		m_Destructor=watcher.m_Destructor;
		m_DestructFunc=watcher.m_DestructFunc;
		m_Counter=watcher.m_Counter;
		IncWatcher();
	}
	void operator=(amyKeeper<T>& keeper)
	{
		DecWatcher();
		TryDestroy();
		m_Destructor=keeper.m_Destructor;
		m_DestructFunc=keeper.m_DestructFunc;
		m_Counter=keeper.m_Counter;
		IncWatcher();
	}
	void operator=(amyWatcher& watcher)
	{
		DecWatcher();
		TryDestroy();
		m_Destructor=keeper.m_Destructor;
		m_DestructFunc=keeper.m_DestructFunc;
		m_Counter=keeper.m_Counter;
		IncWatcher();
	}
	void IncWatcher()
	{
		m_Counter->AddWatcher();
	}
	void DecWatcher()
	{
		m_Counter->DecWatcher();
	}
	void TryDestroy()
	{
		if(m_Counter->HasKeeper()==0&&m_Counter->HasWatcher()==0)
		{
			delete m_Counter;
		}
	}
	bool      HasKeeper()
	{
		return m_Counter->HasKeeper();
	}
	amyKeeper<T> GetKeeper()
	{
		amyKeeper<T> keeper;
		if(m_Counter->HasKeeper())
		{
			keeper.m_Destructor=m_Destructor;
			keeper.m_DestructFunc=m_DestructFunc;
			keeper.m_Counter=m_Counter;
			keeper.IncKeeper();
		}
		return keeper;
	}
	T* GetPointer()const {return (T*)m_Destructor->GetPointer();}
	T* operator->(){return (T*)m_Destructor->GetPointer();}
	operator T*() 
	{
		return this->GetPointer();
	}
	~amyWatcher()
	{
		DecWatcher();
		TryDestroy();
	}
	VoidClass* GetDestructor()
	{
		return m_Destructor;
	}
private:
	VoidClass*                             m_Destructor;
	typename amyKeeper<T>::DestructFunc    m_DestructFunc;
	typename amyKeeper<T>::Counter*        m_Counter;
	template<typename T1> friend bool   operator<(const amyWatcher<T1>& var1,const amyWatcher<T1>& var2);
	template<typename T1> friend bool   operator==(const T1* var1,const amyWatcher<T1>& var2);
	template<typename T1> friend bool   operator==(const amyWatcher<T1>& var1,const T1* var2);
	template<typename T1> friend bool   operator==(const amyWatcher<T1>& var1,const amyWatcher<T1>& var2);
};

template<typename T1>
BASICCRAFT_TEMPLATE_INTERFACE bool    operator<(const amyWatcher<T1>& var1,const amyWatcher<T1>& var2)
{
	return var1.m_Destructor<var2.m_Destructor;
}

template<typename T1>
BASICCRAFT_TEMPLATE_INTERFACE bool    operator==(const T1* var1,const amyWatcher<T1>& var2)
{
	return var1==var2.GetPointer();
}
template<typename T1>
BASICCRAFT_TEMPLATE_INTERFACE bool    operator==(const amyWatcher<T1>& var1,const T1* var2)
{
	return var1.GetPointer()==var2;
}
template<typename T1>
BASICCRAFT_TEMPLATE_INTERFACE bool    operator==(const amyWatcher<T1>& var1,const amyWatcher<T1>& var2)
{
	return var1.GetPointer()==var2.GetPointer();
}
