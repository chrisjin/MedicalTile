#include"amyVariableIO.h"
#include"amyVariableManager.h"
#include<QFile>
#include<QTextStream>
#include"amyVariableHive.h"
#include"amyDebug.h"
amyVariableIO::amyVariableIO(amyVariableHive* p)
{
	m_Parent=p;
}
void amyVariableIO::SetParent(amyVariableHive* p)
{
	m_Parent=p;
}
QDomNode amyVariableIO::CreateNode(QString name)
{
	return this->m_Doc.createElement(name);
}
QString amyVariableIO::GetWorkingPath()
{
	return m_WorkingPath;
}
void amyVariableIO::SetWorkingPath(QString str)
{
	m_WorkingPath=str;
}
QDomNode   amyVariableIO::SerializeContent(amyVariable& var)
{
	QDomElement ele;
	return ele;
}
int amyVariableIO::WriteAttachment(QString dir,amyVariable& var)
{
	return -1;
}
int   amyVariableIO::DeserializeContent(QDomNode node,amyVariable var)
{
	return -1;
}


int amyVariableIO::WriteHeader(amyVariable& var)
{
	amyVariable v=var;
	if(v.GetType()==VTYPE_NULL)
		return 0;
	DOMTAG("name",v.GetName().c_str());
	DOMTAG("type",TYPESTR(v));
	return 1;
}
int amyVariableIO::WriteContent(amyVariable& var)
{
	QDomNode con=SerializeContent(var);
	if(con.isNull())
		return 0;
	this->m_Root.appendChild(con);
	return 1;
}
amyVariable amyVariableIO::DeserializeHeader(QString path)
{
	amyVariable ret;
	return ret;
}

int amyVariableIO::Write(QString dir,amyVariable& v)
{
	SetWorkingPath(dir);
	m_Doc.clear();
	m_Doc.implementation().setInvalidDataPolicy(QDomImplementation::AcceptInvalidChars);
	m_Root = m_Doc.createElement("Var");
	m_Doc.appendChild(m_Root);

	if(0==WriteHeader(v))
	{
		amyWarn("Failed to Write Header");
		return 0;
	}
	if(0==WriteContent(v))
	{
		amyWarn("Failed to Write Content");
		return 0;
	}
	if(0==WriteAttachment(dir,v))
	{
		amyWarn("Failed to Write Attachment");
		return 0;
	}
	SAVEDOM(m_WorkingPath+"/"+v.GetName().c_str()+"_"+m_Parent->GetString()+".var");
	return 1;
}
