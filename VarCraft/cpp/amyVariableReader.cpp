//#include"amyVariableReader.h"
//#include<QFile>
//#include"amyDebug.h"
//#include"amyVariableManager.h"
//#include"amyCube.h"
//#include"amyTypeWrap.h"
//#include"amyDICOM.h"
//#include"amySeriesSet.h"
//amyVariableReader::amyVariableReader()
//{
//
//}
//void amyVariableReader::InitInput()
//{
//
//}
//bool amyVariableReader::Read()
//{
//	QString str=this->GetInput();
//	m_FileInfo=QFileInfo(str);
//
//	QFile file(str);
//	if(!file.open(QFile::ReadOnly)){
//		return 0;
//	}	
//	QString con=file.readAll();
//	if(!m_Doc.setContent(con))
//	{
//		file.close();
//		//amyWarn("XML文件格式错误");
//		return 0;
//	}
//	m_Root = m_Doc.documentElement(); 
//	if(0==ReadHeader())
//		return 0;
//	if(0==ReadAttribute())
//		return 0;
//	if(0==ReadContent())
//		return 0;
//	return 1;
//}
//bool amyVariableReader::ReadHeader()
//{
//	QString name,type;
//	QDomElement ele;
//	ele=m_Root.firstChildElement("name");
//	if(!ele.isNull())
//	{
//		name=ele.text();
//	}
//	else
//	{
//		return 0;
//	}
//	ele=m_Root.firstChildElement("type");
//	if(!ele.isNull())
//	{
//		type=ele.text();
//	}
//	else
//	{
//		return 0;
//	}
//#define ISTYPE(typeenum) (type==amyVariableManager::GetInstance()->GetTypeString(typeenum).c_str())
//	if(ISTYPE(VTYPE_CUBE))
//	{
//		m_Variable=amyVariable::New(VTYPE_CUBE,name.toLocal8Bit().data());
//	}
//	else if(ISTYPE(VTYPE_FLOAT_ARR))
//	{
//		m_Variable=amyVariable::New(VTYPE_FLOAT_ARR,name.toLocal8Bit().data());
//	}
//	else if(ISTYPE(VTYPE_SERIES_SET))
//	{
//		m_Variable=amyVariable::New(VTYPE_SERIES_SET,name.toLocal8Bit().data());
//	}
//	else if(ISTYPE(VTYPE_FLOAT))
//	{
//		m_Variable=amyVariable::New(VTYPE_FLOAT,name.toLocal8Bit().data());
//	}
//	else
//	{
//		return 0;
//	}
//	return 1;
//}
//bool amyVariableReader::ReadAttribute()
//{
//	QDomElement ele;
//	QString     name;
//	switch(m_Variable.GetType())
//	{
//	case VTYPE_CUBE:
//		{
//			ele=m_Root.firstChildElement("attr");
//			name=ele.attribute("name");
//			if(name=="windowcenter")
//			{m_Variable.Get<amyCube>()->windowcenter=ele.text().toInt(); }
//			else if(name=="windowwidth")
//			{m_Variable.Get<amyCube>()->windowwidth=ele.text().toInt(); }
//			else
//			{
//				return 0;
//			}
//			ele=ele.nextSiblingElement("attr");
//			name=ele.attribute("name");
//			if(name=="windowcenter")
//			{m_Variable.Get<amyCube>()->windowcenter=ele.text().toInt(); }
//			else if(name=="windowwidth")
//			{m_Variable.Get<amyCube>()->windowwidth=ele.text().toInt(); }
//			else
//			{
//				return 0;
//			}
//		}
//		break;
//	case VTYPE_FLOAT_ARR:
//		break;
//	}
//	return 1;
//}
//bool amyVariableReader::ReadContent()
//{
//	QDomElement ele;
//	switch(m_Variable.GetType())
//	{
//	case VTYPE_CUBE:
//		{
//			ele=m_Root.firstChildElement("content");
//			QString con=ele.text();
//			QStringList slist=con.split('|');
//			string dir=m_FileInfo.path().toLocal8Bit().data();
//			vector<string> path;
//			for(int i=0;i<slist.count();i++)
//			{
//				if(slist.at(i).size()!=0)
//				path.push_back((dir+"/"+slist.at(i).toLocal8Bit().data()));
//			}
//			m_Variable.Get<amyCube>()->Open(path);
//		}
//		break;
//	case VTYPE_FLOAT_ARR:
//		{
//			ele=m_Root.firstChildElement("content");
//			QString con=ele.text();
//			QStringList slist=con.split('|');
//			for(int i=0;i<slist.count();i++)
//			{
//				if(slist.at(i).size()!=0)
//				m_Variable.Get<amyFloatArr>()->arr.push_back(slist.at(i).toFloat());
//			}
//		}
//		break;
//	case VTYPE_SERIES_SET:
//		{
//			ele=m_Root.firstChildElement("content");
//			amySeriesSet::Keeper k=m_Variable.Get<amySeriesSet>();
//			QDomNodeList serdomlist= ele.elementsByTagName("series");
//			for(int i=0;i<serdomlist.count();i++)
//			{
//				amySeries::Keeper kser=amySeries::New();
//				k->seriesarr.push_back(kser);
//				QDomElement ser=serdomlist.at(i).toElement();
//				///info
//				QDomElement date=ser.firstChildElement("date");
//				if(!date.isNull())
//				{
//					amyDate adate(date.text().toLocal8Bit().data());
//					kser->info->date=adate;
//				}
//				QDomElement seriestime=ser.firstChildElement("seriestime");
//				if(!seriestime.isNull())
//				{
//					kser->info->seriestime=amyTime(seriestime.text().toLatin1().data());
//				}
//				QDomElement acquisitiontime=ser.firstChildElement("acquisitiontime");
//				if(!acquisitiontime.isNull())
//				{
//					kser->info->acquisitiontime=amyTime(acquisitiontime.text().toLatin1().data());
//				}
//				QDomElement plane=ser.firstChildElement("plane");
//				if(!plane.isNull())
//				{
//					kser->info->plane=(amySeriesInfo::ePlane)plane.text().toInt();
//				}
//				///patientinfo
//				amyKeeper<amyPatientInfo> patinfo=kser->patientinfo;
//				QDomElement patientinfo=ser.firstChildElement("patientinfo");
//				QDomElement age=patientinfo.firstChildElement("age");
//				if(!age.isNull())
//				{
//					patinfo->age=age.text().toInt();
//				}
//				QDomElement gender=patientinfo.firstChildElement("gender");
//				if(!gender.isNull())
//				{
//					patinfo->gender=gender.text().toLocal8Bit().data();
//				}
//				QDomElement name=patientinfo.firstChildElement("name");
//				if(!name.isNull())
//				{
//					patinfo->name=name.text().toLocal8Bit().data();
//				}
//				///slicearr
//				QDomElement slicearr=ser.firstChildElement("slicearr");
//				QDomNodeList sliarr=slicearr.elementsByTagName("slice");
//				for(int i=0;i<sliarr.count();i++)
//				{
//					QDomElement slice=sliarr.at(i).toElement();
//					amySlice::Keeper s=amySlice::New();
//					amyKeeper<amySliceInfo> sinfo=s->info;
//					s->seriesinfo=kser->info;
///////////////////////PrepareMacros 
//#define READS(name) \
//	QDomElement name=slice.firstChildElement(#name);\
//	if(!name.isNull())\
//	{\
//		sinfo->name=name.text().toLocal8Bit().data();\
//	}
//#define READN(name,type) \
//	QDomElement name=slice.firstChildElement(#name);\
//	if(!name.isNull())\
//	{\
//		sinfo->name=name.text().to##type();\
//	}
///////////////////////PrepareMacros
//					READS(filepath);
//					READN(imagenumber,Int);
//					READN(slicelocation,Float);
//					READN(slicethickness,Float);
//					READS(seriesuid);
//					READS(seriestime);
//					READN(windowcenter,Int);
//					READN(windowwidth,Int);
//					READN(imagepositionx,Float);
//					READN(imagepositiony,Float);
//					READN(imagepositionz,Float);
//					kser->slicearr.push_back(s);
//				}
//				
//				
//			}
//			
//		}//case VTYPE_SERIES_SET:
//		break;
//	case VTYPE_FLOAT:
//		{
//			ele=m_Root.firstChildElement("content");
//			m_Variable.Get<amyFloat>()->value=ele.text().toFloat();
//		}
//		break;
//	}//switch
//	return 1;
//}