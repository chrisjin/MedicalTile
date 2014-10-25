#pragma once
#include"BasicMacro.h"
#include<string>
using namespace std;
typedef unsigned int uint;


class BASIC_INTERFACE amyDate
{
public:
	void operator=(const char* str);
	amyDate(int ayear,int amonth,int aday):year(ayear),month(amonth),day(aday){}
	amyDate(const char* str);
	amyDate(){};
	uint year;
	uint month;
	uint day;
};
BASIC_INTERFACE bool  operator<(amyDate& t1,amyDate& t2);
BASIC_INTERFACE bool  operator>(amyDate& t1,amyDate& t2);
BASIC_INTERFACE bool  operator==(amyDate& t1,amyDate& t2);
class BASIC_INTERFACE amyTime
{
public:
	void operator=(const char* str);
	void operator+=(int sec);

	amyTime(int ahour,int aminute,int asecond):hour(ahour),minute(aminute),second(asecond){}
	amyTime(const char* str);
	amyTime(){};
	uint hour;
	uint minute;
	uint second;
};
BASIC_INTERFACE bool  operator<(amyTime& t1,amyTime& t2);
BASIC_INTERFACE bool  operator>(amyTime& t1,amyTime& t2);
BASIC_INTERFACE bool  operator==(amyTime& t1,amyTime& t2);
class BASIC_INTERFACE amyRect
{
public:
	amyRect();
	amyRect(int xx,int yy,int awidth,int aheight);
	int x,y;
	unsigned int width,height;

};
template<typename T>
class _amyPoint
{
public:
	_amyPoint(T xx,T yy){x=xx;y=yy;}
	T x,y;
};
typedef _amyPoint<float> amyPoint;

class BASIC_INTERFACE amyLinkNode
{
public:
	amyLinkNode* next;
};

class BASIC_INTERFACE amyLinkTable
{
private:

};


template<class T>
class   BASICCRAFT_TEMPLATE_INTERFACE amyInput
{
public:
	amyInput(){m_IsInit=0;}
	typedef T tInput;
	void SetInput(T input){m_Input=input;InitInput();m_IsInit=1;}
	T GetInput(){return m_Input;}
	bool IsInit(){return m_IsInit;}
	virtual void InitInput(){};
private:
	T m_Input;
	bool m_IsInit;
};


//#define INPUT_DEFINE(classname)\
//public:
//	typedef classname tInput;\
//	void SetInput(classname input){m_Input=input;InitInput();}\
//	classname GetInput(){return m_Input;}\
//	virtual void InitInput(){};\
//private:\
//	classname m_Input;

//#define INPUT_IMPL(classname)\
//	void classname::SetInput()
//template<class T>
//class AMYINTERFACE amySingleton
//{
//public:
//	static T* GetInstance()
//	{
//		if(m_Instance==0)
//		{
//			m_Instance=new T;
//		}
//		return m_Instance;
//	}
//protected:
//	amySingleton(){}
//private:
//	
//	static T* m_Instance;
//
//};
//template<class T>
//AMYINTERFACE T* amySingleton<T>::m_Instance=0;


#define DEFINE_SINGLETON(classname) \
public:\
	static classname* GetInstance();\
private:\
	static classname* m_OneInstance;\

#define IMPLEMENT_SINGLETON(classname)\
	classname* classname::m_OneInstance =0;\
	classname* classname::GetInstance()\
		{\
			if(m_OneInstance)\
			return m_OneInstance;\
			else \
			{\
				m_OneInstance=new classname;\
				return m_OneInstance;\
			}\
		}


