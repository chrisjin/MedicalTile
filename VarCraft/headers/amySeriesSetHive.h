#pragma once
#include"VarMacro.h"
#include"amyVariableHive.h"
#include"amyVariableIO.h"
class amySeriesSetIO;
class VAR_INTERFACE amySeriesSetHive:public amyVariableHive
{
public:
	virtual QImage		GetIcon(amyVariable& var);
	virtual VTYPE		GetType();
	virtual const char* GetString();
	virtual amyVariable Produce(string name);
	virtual amyVariableIO* CreateIO();
};


class amySeriesSetIO:public amyVariableIO
{
public:
	virtual QDomNode     SerializeContent(amyVariable& var);
	virtual int        DeserializeContent(QDomNode node,amyVariable var);
};