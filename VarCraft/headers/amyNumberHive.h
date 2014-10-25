#pragma once
#include"VarMacro.h"
#include"amyVariableHive.h"
#include"amyVariableIO.h"
class VAR_INTERFACE amyNumberHive:public amyVariableHive
{
public:
	virtual QImage		   GetIcon(amyVariable& var);
	virtual VTYPE		   GetType();
	virtual const char*	   GetString();
	virtual amyVariableIO* CreateIO();
	virtual amyVariable    Produce(string name);
};

class amyNumberIO:public amyVariableIO
{
public:
	virtual QDomNode     SerializeContent(amyVariable& var);
	virtual int        DeserializeContent(QDomNode node,amyVariable var);
};