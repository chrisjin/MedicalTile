#include"amySeriesSetHive.h"
#include"amySeriesSet.h"
#include<QDomDocument>
#include"amyDICOM.h"
amyVariableIO* amySeriesSetHive::CreateIO()
{
	return new amySeriesSetIO;
}
QImage		amySeriesSetHive::GetIcon(amyVariable& var)
{
	return QImage(":/ICON/Patient"); 
}
VTYPE		amySeriesSetHive::GetType()
{
	return VTYPE_SERIES_SET;
}
const char* amySeriesSetHive::GetString()
{
	return "SSET";
}
amyVariable amySeriesSetHive::Produce(string name)
{
	amyVariable v(GetType(),name,new amySeriesSet);
	return v;
}


QDomNode   amySeriesSetIO::SerializeContent(amyVariable& v)
{
	amySeriesSet::Keeper k=v.Get<amySeriesSet>();
	QDomDocument m_Doc=this->GetDoc();
	QDomElement m_Root = m_Doc.createElement("content");
	QDomElement child=m_Root;
	for(int i=0;i<k->seriesarr.size();i++)
	{
		QDomElement series=m_Doc.createElement("series");
		child.appendChild(series);
		amySeries* ser=k->seriesarr[i].GetPointer();
		////////info
		amySeriesInfo* sei=ser->info.GetPointer();
		amyDate date=sei->date;
		amyTime seriestime=sei->seriestime;
		amyTime acquisitiontime=sei->acquisitiontime;
		amySeriesInfo::ePlane plane=sei->plane;
		DOMCTAG(series,"date",           DATE2STR(date));
		DOMCTAG(series,"seriestime",     TIME2STR(seriestime));
		DOMCTAG(series,"acquisitiontime",TIME2STR(acquisitiontime));
		DOMCTAG(series,"plane",          PLANE2STR(plane));

		///////patientinfo
		if(!ser->patientinfo.IsNull())
		{
			QDomElement patientinfo=m_Doc.createElement("patientinfo");
			series.appendChild(patientinfo);
			amyPatientInfo* pinfo=ser->patientinfo.GetPointer();
			DOMCTAG(patientinfo,"age",QString::number(pinfo->age));
			DOMCTAG(patientinfo,"gender",pinfo->gender.c_str());
			DOMCTAG(patientinfo,"name",pinfo->name.c_str());
		}

		//////slicearr
		QDomElement slicearr=m_Doc.createElement("slicearr");
		series.appendChild(slicearr);
		for(int i=0;i<ser->slicearr.size();i++)
		{
			QDomElement slice=m_Doc.createElement("slice");
			slicearr.appendChild(slice);

			amySliceInfo* si=ser->slicearr[i]->info.GetPointer();
			SATTR( filepath);
			NATTR( imagenumber);
			NATTR( slicelocation);
			NATTR( slicethickness);
			SATTR( seriesuid);
			SATTR( seriestime);
			NATTR( windowcenter);
			NATTR( windowwidth);
			NATTR( imagepositionx);
			NATTR( imagepositiony);
			NATTR( imagepositionz);
		}

	}//for
	return m_Root;
}
int   amySeriesSetIO::DeserializeContent(QDomNode node,amyVariable var)
{
	QDomElement ele=node.toElement();
	amySeriesSet::Keeper k=var.Get<amySeriesSet>();
	QDomNodeList serdomlist= ele.elementsByTagName("series");
	for(int i=0;i<serdomlist.count();i++)
	{
		amySeries::Keeper kser=amySeries::New();
		k->seriesarr.push_back(kser);
		QDomElement ser=serdomlist.at(i).toElement();
		///info
		QDomElement date=ser.firstChildElement("date");
		if(!date.isNull())
		{
			amyDate adate(date.text().toLocal8Bit().data());
			kser->info->date=adate;
		}
		QDomElement seriestime=ser.firstChildElement("seriestime");
		if(!seriestime.isNull())
		{
			kser->info->seriestime=amyTime(seriestime.text().toLatin1().data());
		}
		QDomElement acquisitiontime=ser.firstChildElement("acquisitiontime");
		if(!acquisitiontime.isNull())
		{
			kser->info->acquisitiontime=amyTime(acquisitiontime.text().toLatin1().data());
		}
		QDomElement plane=ser.firstChildElement("plane");
		if(!plane.isNull())
		{
			kser->info->plane=(amySeriesInfo::ePlane)plane.text().toInt();
		}
		///patientinfo
		amyKeeper<amyPatientInfo> patinfo=kser->patientinfo;
		QDomElement patientinfo=ser.firstChildElement("patientinfo");
		QDomElement age=patientinfo.firstChildElement("age");
		if(!age.isNull())
		{
			patinfo->age=age.text().toInt();
		}
		QDomElement gender=patientinfo.firstChildElement("gender");
		if(!gender.isNull())
		{
			patinfo->gender=gender.text().toLocal8Bit().data();
		}
		QDomElement name=patientinfo.firstChildElement("name");
		if(!name.isNull())
		{
			patinfo->name=name.text().toLocal8Bit().data();
		}
		///slicearr
		QDomElement slicearr=ser.firstChildElement("slicearr");
		QDomNodeList sliarr=slicearr.elementsByTagName("slice");
		for(int i=0;i<sliarr.count();i++)
		{
			QDomElement slice=sliarr.at(i).toElement();
			amySlice::Keeper s=amySlice::New();
			amyKeeper<amySliceInfo> sinfo=s->info;
			s->seriesinfo=kser->info;
			/////////////////////PrepareMacros 
#define READS(name) \
	QDomElement name=slice.firstChildElement(#name);\
	if(!name.isNull())\
			{\
			sinfo->name=name.text().toLocal8Bit().data();\
			}
#define READN(name,type) \
	QDomElement name=slice.firstChildElement(#name);\
	if(!name.isNull())\
			{\
			sinfo->name=name.text().to##type();\
			}
			/////////////////////PrepareMacros
			READS(filepath);
			READN(imagenumber,Int);
			READN(slicelocation,Float);
			READN(slicethickness,Float);
			READS(seriesuid);
			READS(seriestime);
			READN(windowcenter,Int);
			READN(windowwidth,Int);
			READN(imagepositionx,Float);
			READN(imagepositiony,Float);
			READN(imagepositionz,Float);
			kser->slicearr.push_back(s);
		}


	}

	return 1;
}