#pragma once
#include"BasicMacro.h"
#include"AllCast.h"
class VoidClass
{
public:
	VoidClass()
	{
		m_Pointer=0;
	}
	VoidClass(void* p)
	{
		m_Pointer=p;
	}
	void* GetPointer(){return m_Pointer;}
	bool  IsNull(){return m_Pointer==0?1:0;}
private:
	void* m_Pointer;
};

template<typename T>
class Destructor:public VoidClass
{
public:
	Destructor(T* p):VoidClass(p)
	{
	}
	void Do()
	{
		delete ((T*)GetPointer());
	}
};
class CrapCounter
{
public:
	CrapCounter(){m_KeeperCount=0;m_WatcherCount=0;}
	void AddKeeper(){m_KeeperCount++;}
	void DecKeeper(){m_KeeperCount--;}
	void AddWatcher(){m_WatcherCount++;}
	void DecWatcher(){m_WatcherCount--;}
	bool HasKeeper(){return m_KeeperCount>0?1:0;}
	bool HasWatcher(){return m_WatcherCount>0?1:0;}
private:
	unsigned int m_KeeperCount;
	unsigned int m_WatcherCount;
	template<typename T> friend class amyKeeper;
};
template<typename T>
class BASICCRAFT_TEMPLATE_INTERFACE amyKeeper
{
public:
	typedef CrapCounter Counter;
	void IncKeeper(){m_Counter->AddKeeper();}
	void DecKeeper(){m_Counter->DecKeeper();}
	void TryDestroy()
	{
		if(m_Counter->HasKeeper()==0)
		{
			if(m_Destructor)
			{
				(m_Destructor->*m_DestructFunc)();
				delete m_Destructor;
				m_Destructor=0;
			}
			if(m_Counter->HasWatcher()==0)
			{
				delete m_Counter;
				m_Counter=0;
			}
		}
	}
	~amyKeeper()
	{
		DecKeeper();
		TryDestroy();
	}
	amyKeeper()
	{
		m_Destructor=0;
		m_Counter=new Counter;  
		IncKeeper(); 
	}
	template<typename T1>
	amyKeeper(T1* p)
	{
		typedef void(Destructor<T1>::*RawDestructFunc)();
		Destructor<T1>* dtor=new Destructor<T1>(p);
		m_Destructor=(VoidClass*)(dtor);
		m_DestructFunc=All_cast<RawDestructFunc,DestructFunc>(&Destructor<T1>::Do);
		m_Counter=new Counter;  
		IncKeeper(); 
	}
	template<typename T1>
	amyKeeper(const amyKeeper<T1>& var)
	{
		m_Counter=var.m_Counter;
		m_Destructor=var.m_Destructor;   
		m_DestructFunc=var.m_DestructFunc;
		IncKeeper(); 
	}
	amyKeeper(const amyKeeper& var)
	{
		m_Counter=var.m_Counter;
		m_Destructor=var.m_Destructor;   
		m_DestructFunc=var.m_DestructFunc;
		IncKeeper();         
	}
	void operator=(const amyKeeper& var)
	{
		this->DecKeeper();
		TryDestroy();
		m_Counter=var.m_Counter;
		m_Destructor=var.m_Destructor;
		m_DestructFunc=var.m_DestructFunc;
		IncKeeper();
	}
	template<typename T1>
	void operator=(const amyKeeper<T1>& var)
	{
		this->DecKeeper();
		TryDestroy();
		m_Counter=var.m_Counter;
		m_Destructor=var.m_Destructor;
		m_DestructFunc=var.m_DestructFunc;
		IncKeeper();
	}
	template<typename T1>
	void operator=(T1* p)
	{		
		this->DecKeeper();
		TryDestroy();
		typedef void(Destructor<T1>::*RawDestructFunc)();
		Destructor<T1>* dtor=new Destructor<T1>(p);
		m_Destructor=(VoidClass*)(dtor);
		m_DestructFunc=All_cast<RawDestructFunc,DestructFunc>(&Destructor<T1>::Do);
		m_Counter=new Counter;  
		IncKeeper(); 
	}
	template<typename T1>
	void Cast(amyKeeper<T1>& var)
	{
		this->DecKeeper();
		TryDestroy();
		m_Counter=var.GetCounter();
		m_Destructor=var.GetDestructor();
		m_DestructFunc=var.GetDestructFunc();
		IncKeeper();
	}
	template<typename T1>
	amyKeeper<T1> CastTo()
	{
		amyKeeper<T1> ret;
		ret.Cast(*this);
		return ret;
	}
	typedef void(VoidClass::*DestructFunc)();
	T* GetPointer(){return (T*)m_Destructor->GetPointer();}
	T* operator->(){return (T*)m_Destructor->GetPointer();}
	Counter*      GetCounter(){return m_Counter;}
	VoidClass*    GetDestructor(){return m_Destructor;}
	DestructFunc  GetDestructFunc(){return m_DestructFunc;}
	bool          IsNull()
	{
		if(m_Destructor)
			return m_Destructor->IsNull();
		else
			return 1;
	}
	template<typename T1>
	bool          operator==(amyKeeper<T1>& var)
	{
		if(this->m_Destructor==var.GetDestructor())
			return 1;
		else 
			return 0;
	}
	template<typename T1>
	bool          operator<(amyKeeper<T1>& var)
	{
		return this->m_Destructor<var.GetDestructor();
	}
	operator T*() 
   {
	   return this->GetPointer();
   }
private:

	
	VoidClass*     m_Destructor;
	DestructFunc   m_DestructFunc;
	Counter        *m_Counter;

	friend class amyKeeper<void>;
	template<typename T1> friend class amyWatcher;  
};

//template<typename T>
//class DICOMCRAFT_TEMPLATE_INTERFACE amyNew
//{
//public:
//typedef amyKeeper<T> Keeper;
//static Keeper New(){return new T;}
//protected:
//	amyNew(){}
//};
#define NEW_MACRO(classname) \
public:\
	typedef amyKeeper<classname> Keeper;\
	static Keeper New(){return new classname;}

#define NEW_MACRO_WITH_ARG(classname,argtype)\
public:\
	typedef amyKeeper<classname> Keeper;\
	static Keeper New(argtype arg){return new classname(arg);}
//template<typename T1,typename T2>
//amyKeeper<T2> SuperCast(amyKeeper<T1> p)
//{
//	amyKeeper<T2> pt((T2*)p.GetPointer());
//	return pt;
//}
