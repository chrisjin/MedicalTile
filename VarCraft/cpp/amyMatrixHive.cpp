#include"amyMatrixHive.h"
#include"amyMatrix.h"
#include<QStringList>
#include<QPainter>
amyVariableIO* amyMatrixHive::CreateIO()
{
	return new amyMatrixIO;
}
QImage amyMatrixHive::GetIcon(amyVariable& var)
{
	FETCH(amyMatrix,kdata,var);
	QImage image(64,64,QImage::Format_ARGB32);
	QPainter p(&image);
	p.fillRect(QRect(0,0,64,64),QColor(160,160,160));
	QString str="";
	str=str.sprintf("<%d Arr>",kdata.rowcount());
	p.drawText(QRect(0,0,64,64),Qt::AlignCenter,str);
	return image;
}
VTYPE		amyMatrixHive::GetType()
{
	return VTYPE_DATA_MATRIX;
}
amyVariable amyMatrixHive::Produce(string name)
{
	amyVariable v(GetType(),name,new amyMatrix);
	return v;
}


const char* amyMatrixHive::GetString()
{
	return "DMAT";
}
QDomNode   amyMatrixIO::SerializeContent(amyVariable& v)
{
	QDomDocument m_Doc=this->GetDoc();
	QDomElement m_Root = m_Doc.createElement("content");
	FETCH(amyMatrix,k,v);
	for(int i=0;i<k.rowcount();i++)
	{
		QString con="";
		for(int j=0;j<k[i].size();j++)
		{
			con+=QString::number(k[i][j])+"|";
		}
		DOMTAG("array",con);
	}
	
	return m_Root;
}
int   amyMatrixIO::DeserializeContent(QDomNode node,amyVariable var)
{
	if(node.isNull())
		return 0;
	QDomNodeList ld=node.toElement().elementsByTagName("array");
	FETCH(amyMatrix,data,var);
	for(int i=0;i<ld.size();i++)
	{
		QString con=ld.at(i).toElement().text();
		QStringList slist=con.split('|');
		amyArray& arr=data.addrow();
		for(int j=0;j<slist.size();j++)
		{
			if(slist.at(j).size()!=0)
			{
				float a=slist.at(j).toFloat();
				arr().push_back(a);
			}
		}
	}
	return 1;
}