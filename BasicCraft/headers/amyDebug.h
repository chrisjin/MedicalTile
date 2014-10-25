#pragma once
#include"BasicMacro.h"
#include<windows.h>
#define _ATB {\
                 bool arr[]={
#define _ATE \
                    };\
                 for(int i=0;i<sizeof(arr)/sizeof(bool);i++)       \
                 {\
                   if(arr[i]==0)\
                   {\
                       char error[100];\
                       sprintf(error,"%s\nLINE:%d\nNO.%d ASSERT FAILED\n",__FILE__,__LINE__,i+1);\
                       MessageBoxA(0,error,"I TELL YOU",MB_OK);\
                   }\
                 }\
             }while(0);


void BASIC_INTERFACE _amyWarn(int line,const char* filename,const char* fmt);
#define amyWarn(con) _amyWarn(__LINE__,__FILE__,con)
class KidTest
{	
public:
	KidTest(){};
	void Run(const char* name);
	virtual void Body()=0;
};

#define RUNTEST(name)\
{\
	name t;\
	t.Run(#name);\
}

class INIT_CONSOLE
{
};