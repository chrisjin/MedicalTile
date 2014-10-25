#include"amyNumberHive.h"
#include<QPainter>
#include"amyNumber.h"
#include<QDomElement>
QImage		   amyNumberHive::GetIcon(amyVariable& var)
{
	FETCH(amyNumber,kdata,var);
	QImage image(64,64,QImage::Format_ARGB32);
	QPainter p(&image);
	p.fillRect(QRect(0,0,64,64),QColor(160,160,160));
	QString str="";
	str=str.sprintf("Val:\n%0.2f",kdata());
	p.drawText(QRect(0,0,64,64),Qt::AlignCenter,str);
	return image;
}
VTYPE		   amyNumberHive::GetType()
{
	return VTYPE_DATA_NUMBER;
}
const char*	   amyNumberHive::GetString()
{
	return "DNUM";
}
amyVariableIO* amyNumberHive::CreateIO()
{
	return new amyNumberIO;
}
amyVariable    amyNumberHive::Produce(string name)
{
	amyVariable v(GetType(),name,new amyNumber);
	return v;
}

QDomNode     amyNumberIO::SerializeContent(amyVariable& var)
{
	QDomDocument m_Doc=this->GetDoc();
	QDomElement m_Root = m_Doc.createElement("content");
	FETCH(amyNumber,k,var);
	DOMTAG("array",QString::number(k()));
	return m_Root;
}
int        amyNumberIO::DeserializeContent(QDomNode node,amyVariable var)
{
	QDomNodeList ld=node.toElement().elementsByTagName("content");
	if(ld.size()==0)
		return 0;
	FETCH(amyNumber,k,var);
	k()=ld.at(0).toElement().text().toFloat();
	return 1;
}