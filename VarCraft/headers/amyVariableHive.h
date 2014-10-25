#pragma once
#include"amyVariable.h"
#include"amyTypes.h"
#include<QImage>
#include<QString>
class amyVariableIO;

class amyVariableHive
{
public:
	amyVariableHive();
	virtual QImage             GetIcon(amyVariable& var)=0;
	virtual VTYPE              GetType()=0;
	virtual const char*        GetString()=0;
	virtual amyVariable        Produce(string name)=0;
	virtual amyVariableIO*     CreateIO();
	amyVariableIO*			   GetIO();
private:
	amyVariableIO* m_IO;
};