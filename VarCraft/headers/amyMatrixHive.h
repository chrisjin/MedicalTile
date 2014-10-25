#pragma once
#include"VarMacro.h"
#include"amyVariableHive.h"
#include"amyVariableIO.h"
class amyDataIO;
class VAR_INTERFACE amyMatrixHive:public amyVariableHive
{
public:
	virtual QImage		   GetIcon(amyVariable& var);
	virtual VTYPE		   GetType();
	virtual const char*	   GetString();
	virtual amyVariableIO* CreateIO();
	virtual amyVariable    Produce(string name);
};

class amyMatrixIO:public amyVariableIO
{
public:
	virtual QDomNode     SerializeContent(amyVariable& var);
	virtual int        DeserializeContent(QDomNode node,amyVariable var);
};