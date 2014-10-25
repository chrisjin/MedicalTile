#include"amyXMLAlgorithm.h"
#include <QDomDocument>
#include<QFile>
#include"amyAlgorithmManager.h"
#include<QMessageBox>
#include"amyAlgorithmStack.h"
#include"amyDebug.h"
#include"amyAlgorithmRunner.h"
bool amyXMLAlgorithm::CheckInputArr(vector<amyVariable>& arr)
{
	if(m_AlgorithmArr.size()==0)
		return 0;
	return m_AlgorithmArr[0]->CheckInputArr(arr);
}

 const char* amyXMLAlgorithm::GetAlgorithmName()
{
	return m_Name.c_str();
}

void  amyXMLAlgorithm::Run()
{
	for(int i=0;i<m_AlgorithmArr.size();i++)
	{
		if(0==amyAlgorithmRunner::GetInstance()->Start(m_AlgorithmArr[i]))
			return;
	}
}

bool amyXMLAlgorithm::LoadXML(QString filename,amyAlgorithmManager* am)
{
	QDomDocument dom;
	QFile file(filename);
	if(!file.open(QFile::ReadOnly)){
		return 0;
	}
	QString con=file.readAll();
	if(!dom.setContent(con))
	{
		file.close();
		amyWarn("XML文件格式错误");
		return 0;
	}
	QDomElement root = dom.documentElement(); 
	QDomElement version=root.childNodes().at(0).toElement();
	if(version.text()!="1")
	{
		file.close();
		return 0;
	}
	if(version.tagName().toLower()!="version")
	{
		file.close();
		return 0;
	}
	QDomElement name=root.childNodes().at(1).toElement();
	if(name.tagName().toLower()!="name")
	{
		file.close();
		return 0;
	}
	else
	{
		this->m_Name=name.text().toLatin1().data();
	}
	QDomElement category=root.childNodes().at(2).toElement();
	if(category.tagName().toLower()!="category")
	{
		m_Category="Algorithm";
	}
	else
	{
		m_Category=category.text().toLatin1().data();
	}
	QDomNodeList nodelist=root.elementsByTagName("algo");
	int lastoutputnum=0;
	for(int i=0;i<nodelist.count();i++)
	{
		QString algname=nodelist.at(i).toElement().text();
		amyAlgorithm* al=am->GetAlgorithmByName(algname);
		if(al)
		{
			//if(i>0&&lastoutputnum!=al->GetInputNum())
			//{
			//	QMessageBox::warning(0,"warning","输入输出不一致");
			//}
			this->m_AlgorithmArr.push_back(al);
			//lastoutputnum=al->GetOutputNum();
		}
	}
	if(this->m_AlgorithmArr.size()==0)
		return 0;
	return 1;
}