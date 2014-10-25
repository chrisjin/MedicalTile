#pragma once
#include"VarMacro.h"
#include"amyVariable.h"
#include"amyCube.h"
#include"amyTypeWrap.h"

#include<QString>


class VAR_INTERFACE amySerialize
{
public:
	static bool Variable(QString path,amyVariable& vararr);
};

class VAR_INTERFACE amyDeserialize
{
public:
	//static bool   IsNeedConvert(QString path);
	//static void   ConvertForCompatibility(QString path);
	static amyVariable Variable(QString path);
	static bool Variable(QString path,vector<amyVariable>& vararr);
	//static amyVariable Variable(QString path,vector<amyVariable>& vararr);
};