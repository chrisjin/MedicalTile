#include"amyDebug.h"
#include<stdio.h>
#include<string>
using namespace std;
void _amyWarn(int line,const char* filename,const char* fmt)
{
	string str;
	str+=fmt;
	str+="\nLine:%d";
	str+="\nFile:";
	str+=filename;
	char out[1024];
	sprintf(out,str.c_str(),line);
	MessageBoxA(0,out,"I TELL YOU",MB_OK);       // 译注：输出格式化后的字符串到调试器
}
