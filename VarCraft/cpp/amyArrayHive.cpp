#include"amyArrayHive.h"
#include"amyArray.h"
#include<QStringList>
#include<QPainter>
QImage amyArrayHive::GetIcon(amyVariable& var)
{
	FETCH(amyArray,arr,var);
	QImage image(64,64,QImage::Format_ARGB32);
	QPainter p(&image);
	p.fillRect(QRect(0,0,64,64),QColor(160,160,160));
	QString str;
	str=str.sprintf("<%d Num>",arr.size());
	p.drawText(QRect(0,0,64,64),Qt::AlignCenter,str);
	return image;
}
VTYPE amyArrayHive::GetType()
{
	return VTYPE_DATA_ARRAY;
}
const char*	   amyArrayHive::GetString()
{
	return "DARR";
}
amyVariableIO* amyArrayHive::CreateIO()
{
	return new amyArrayIO;
}
amyVariable    amyArrayHive::Produce(string name)
{
	amyVariable v(GetType(),name,new amyArray);
	return v;
}

QDomNode     amyArrayIO::SerializeContent(amyVariable& var)
{
	QDomDocument m_Doc=this->GetDoc();
	QDomElement m_Root = m_Doc.createElement("content");
	FETCH(amyArray,k,var);
	QString con="";
	for(int i=0;i<k.size();i++)
	{
		con+=QString::number(k[i])+"|";
		
	}
	DOMTAG("array",con);
	return m_Root;
}
int        amyArrayIO::DeserializeContent(QDomNode node,amyVariable var)
{
	if(node.isNull())
		return 0;
	QDomNodeList ld=node.toElement().elementsByTagName("array");
	FETCH(amyArray,data,var);
	if(ld.size()==0)
		return 0;
	QDomElement  line=ld.at(0).toElement();
	QString con=line.text();
	QStringList slist=con.split('|');

	for(int j=0;j<slist.size();j++)
	{
		if(slist.at(j).size()!=0)
		{
			float a=slist.at(j).toFloat();
			data().push_back(a);
		}
	}
	return 1;
}