#pragma once
#include"amyAlgorithm.h"
#include<QApplication>
class amyAlgorithmStack;
class amyDLLSubtractionAlgorithm:public amyAlgorithm
{
public:
	amyDLLSubtractionAlgorithm(amyAlgorithmStack* input);
	virtual bool   CheckArgumetType(int index,VTYPE t)
	{
		if(t==VTYPE_CUBE)return 1;
		else return 0;
	}
	virtual string GetAlgorithmName(){return "QtDllSubtraction";}
	virtual int    GetOutputNum(){return 1;}
	virtual int    GetInputNum(){return 2;}
	virtual void   Run();
	QApplication *m_App;
};
extern "C"
{
_declspec(dllexport) amyAlgorithm*   GetAlgorithm(amyAlgorithmStack* input);
}

BOOL APIENTRY DllMain( HANDLE hModule,     //HANDLE是句柄类型的关键字
       DWORD ul_reason_for_call,       //DWORD是双字
       LPVOID lpReserved       //LPVOID是一个没有类型的指针，也就是说你可以将任意类型的指针赋值给LPVOID类型的变量（一般作为参数传递），然后在使用的时候在转换回来。
       )
{
switch(ul_reason_for_call) 
{ 
case DLL_PROCESS_ATTACH: 
	{
	int a;
  // QApplication *app=new QApplication(a,(char**)0);
	}
   break; 
case DLL_PROCESS_DETACH: 
   break; 
}
return TRUE;
}