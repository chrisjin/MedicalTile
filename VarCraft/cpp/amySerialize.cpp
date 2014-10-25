#include"amySerialize.h"
#include "itkImage.h"
#include "itkImageFilewriter.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkGDCMImageIO.h"
#include<QDir>
#include"amyTypeWrap.h"

#include"amyCube.h"
#include"amyVariableHive.h"
#include"amyVariableManager.h"
#include"amyVariableIO.h"
#include"amyDebug.h"
bool amySerialize::Variable(QString path,amyVariable& v)
{
	amyVariableManager* vm=amyVariableManager::GetInstance();
	amyVariableHive*    hv=vm->GetHive(v.GetType());
	if(hv)
	{
		amyVariableIO* io=hv->GetIO();
		if(io)
		{
			return io->Write(path,v);
		}
		else
		{
			amyWarn("The Corresponding IO Not Found");
		}
	}
	else
	{
		amyWarn("Hive Not Found,Type Incomplete");
	}
	return 0;
}

void   ConvertForCompatibility(QDomDocument m_Doc,QDomElement m_Root)
{
	QDomNodeList ele=m_Root.elementsByTagName("type");
	if(ele.size()>0)
		if(ele.at(0).toElement().text()=="FARR")
		{
			ele.at(0).firstChild().setNodeValue("DARR");
			QString str=ele.at(0).toElement().text();
			QDomNodeList nl=m_Root.elementsByTagName("content");
			if(nl.size()==0)
				return;
			QDomElement content=nl.at(0).toElement();
			QString numlist=content.text();
			content.removeChild(content.firstChild());
			DOMCTAG(content,"array",numlist)
			return;
		}
	ele=m_Root.elementsByTagName("attr");
	if(ele.size()==2)
	{
		QDomNode n1=ele.at(0);
		QDomNode n2=ele.at(1);
		QString windowcenter=n1.toElement().text();
		QString windowwidth=n2.toElement().text();
		m_Root.removeChild(n1);
		m_Root.removeChild(n2);
		QDomNodeList nl=m_Root.elementsByTagName("content");
		if(nl.size()==0)
			return;
		QDomElement content=nl.at(0).toElement();
		QString filelist=content.text();
		content.removeChild(content.firstChild());
		DOMCTAG(content,"windowcenter",windowcenter)
		DOMCTAG(content,"windowwidth",windowwidth)
		DOMCTAG(content,"files",filelist)
		QString debug=m_Doc.toString();
		return;
	}

}
amyVariable amyDeserialize::Variable(QString path)
{
	amyVariable ret;
	QDomDocument m_Doc;
	QDomElement  m_Root,name,type,content;
	amyVariableManager* vm;
	amyVariableHive*   hv;
	amyVariableIO* io;
	QFileInfo info(path);
	QFile	  file(path);
	if(!file.open(QFile::ReadOnly)){
		amyWarn("File Not Found");
		return ret;
	}	
	QString con=file.readAll();
	if(!m_Doc.setContent(con))
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	m_Root = m_Doc.documentElement(); 
	ConvertForCompatibility(m_Doc,m_Root);
	name=m_Root.firstChild().toElement();
	if(name.isNull())
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	else if(name.tagName()!="name")
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	type=name.nextSibling().toElement();
	if(type.isNull())
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	else if(type.tagName()!="type")
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	content=type.nextSibling().toElement();
	if(type.isNull())
	{
		amyWarn("Wrong File Format");
		goto END;
	}
	vm=amyVariableManager::GetInstance();
	hv=vm->GetHiveByString(type.text());
	if(hv==0)
	{
		amyWarn("Hive Not Found");
		goto END;
	}
	ret=hv->Produce(name.text().toLocal8Bit().data());
	io=hv->GetIO();
	io->SetWorkingPath(info.path());
	if(io->DeserializeContent(content,ret)!=1)
	{
		amyWarn("Error in Deserialize");
		ret=amyVariable();
		goto END;
	}

END:
		file.close();
		return ret;
}

bool amyDeserialize::Variable(QString path,vector<amyVariable>& vararr)
{
	QFileInfo fileinfo(path);
	if(fileinfo.isDir())
	{
		QDir dir;  
		dir.setPath(path);
		QStringList filter;
		filter<<"*.var";
		dir.setNameFilters(filter);
		dir.setFilter(QDir::Files | QDir::NoSymLinks);
		QFileInfoList infolist = dir.entryInfoList (QDir::Files | QDir::NoDotAndDotDot);
		QFileInfoList::Iterator itr=infolist.begin();
		for(;itr!=infolist.end();itr++)
		{
			amyVariable v=Variable(itr->absoluteFilePath());
			if(v.GetType()!=VTYPE_NULL)
				vararr.push_back(v);
		}
		return 1;
	}
	else if(fileinfo.isFile())
	{
		amyVariable v=Variable(path);
		if(v.GetType()!=VTYPE_NULL)
			vararr.push_back(v);
	}
	return 0;

}