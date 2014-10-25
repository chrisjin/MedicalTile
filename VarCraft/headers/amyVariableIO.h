#pragma once
#include"VarMacro.h"
#include"amyVariable.h"
#include<QString>
#include<QDomDocument>
class amyVariableHive;
class amyVariableIO
{
public:
	amyVariableIO(){}
	amyVariableIO(amyVariableHive* p);
	void					   SetParent(amyVariableHive* p);
	amyVariableHive*           GetHive(){return m_Parent;}
	QDomDocument               GetDoc(){return m_Doc;}
	QDomElement				   GetRoot(){return m_Root;}
	QDomNode                   CreateNode(QString name);
	QString					   GetWorkingPath();
	void					   SetWorkingPath(QString str);
	int                        WriteHeader(amyVariable& var);
	int                        WriteContent(amyVariable& var);
	virtual QDomNode           SerializeContent(amyVariable& var);
	virtual int                WriteAttachment(QString dir,amyVariable& var);
	int					       Write(QString dir,amyVariable& var);

	amyVariable				   DeserializeHeader(QString content);
	virtual int				   DeserializeContent(QDomNode node,amyVariable var);
	
private:
	QDomDocument m_Doc;
	QDomElement  m_Root;
	QString      m_WorkingPath;
	amyVariableHive* m_Parent;
};