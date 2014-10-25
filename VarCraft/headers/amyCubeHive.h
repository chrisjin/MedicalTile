#pragma once
#include"VarMacro.h"
#include"amyVariableHive.h"
#include<QString>
#include"amyVariableIO.h"

using namespace std;
class amyCubeIO;
class VAR_INTERFACE amyCubeHive:public amyVariableHive
{
public:
	virtual QImage		GetIcon(amyVariable& var);
	virtual VTYPE		GetType();
	virtual const char* GetString();
	virtual amyVariable Produce(string name);
	virtual amyVariableIO* CreateIO();
private:

};

class amyCubeIO:public amyVariableIO
{
public:
	virtual QDomNode     SerializeContent(amyVariable& var);
	virtual int        WriteAttachment(QString dir,amyVariable& var);
	virtual int        DeserializeContent(QDomNode node,amyVariable var);
	vector<QString>&    PathArr(){return m_FilePathArr;}
private:
	QString      m_WorkingPath;
	vector<QString> m_FilePathArr;
};