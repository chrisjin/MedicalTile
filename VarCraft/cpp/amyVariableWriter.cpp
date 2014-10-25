//#include"amyVariableWriter.h"
//#include"amyVariable.h"
//#include<QFile>
//#include<QTextStream>
//#include"amyTypeWrap.h"
//#include"amyVariableManager.h"
//#include"amyDICOM.h"
//#include"amySeriesSet.h"
////#include"amySerializeUtil.h"
//
//amyVariableWriter::amyVariableWriter(QString workingpath)
//{
//	m_WorkingPath=workingpath;
//	m_Root = m_Doc.createElement("Var");
//	m_Doc.appendChild(m_Root);
//}
//bool amyVariableWriter::Write()
//{
//	WriteHeader();
//	WriteAttribute();
//	WriteContent();
//	amyVariable v=this->GetInput();
//	SAVEDOM(m_WorkingPath+"/"+v.GetName().c_str()+".var");
//	return 1;
//}
//void amyVariableWriter::WriteHeader()
//{
//	amyVariable v=this->GetInput();
//	DOMTAG("name",v.GetName().c_str());
//	DOMTAG("type",TYPESTR(v));
//}
//void amyVariableWriter::WriteAttribute()
//{
//	amyVariable v=this->GetInput();
//	switch(v.GetType())
//	{
//	case VTYPE_CUBE:
//		{
//			amyCube::Keeper k=v.Get<amyCube>();
//			DOMATTR("int","windowcenter",QString::number(k->windowcenter));
//			DOMATTR("int","windowwidth",QString::number(k->windowwidth));
//		}
//		break;
//	case VTYPE_SERIES_SET:
//		{
//			//amySeriesSet::Keeper k=v.Get<amySeriesSet>();
//			//k->
//		}
//		break;
//	}
//}
//void amyVariableWriter::WriteContent()
//{
//	amyVariable v=this->GetInput();
//	switch(v.GetType())
//	{
//	case VTYPE_CUBE:
//		{
//			amyCube::Keeper cube=v.Get<amyCube>();
//			amyCube::tCube::RegionType   region     = cube->obj->GetLargestPossibleRegion();
//			amyCube::tCube::IndexType    start      = region.GetIndex();
//			amyCube::tCube::SizeType     size       = region.GetSize();
//
//			const unsigned int firstSlice = start[2];
//			const unsigned int lastSlice  = start[2] + size[2] - 1;
//
//			QString nameformat=(v.GetName()+"%03d").c_str();
//			QString str;
//			QString con;
//			for(int i=firstSlice;i<=lastSlice;i++)
//			{
//				str.sprintf(nameformat.toLocal8Bit().data(),i);
//				con+=str+"|";
//				m_FilePathArr.push_back(m_WorkingPath+"/"+str);
//			}
//			DOMTAG("content",con);
//		}
//		break;
//	case VTYPE_FLOAT_ARR:
//		{
//			QString con="";
//			amyFloatArr::Keeper k=v.Get<amyFloatArr>();
//			for(int i=0;i<k->arr.size();i++)
//			{
//				con+=QString::number(k->arr[i])+"|";
//			}
//			DOMTAG("content",con);
//		}
//		break;
//	case VTYPE_SERIES_SET:
//		{
//
//			amySeriesSet::Keeper k=v.Get<amySeriesSet>();
//			QDomElement child= m_Doc.createElement("content");
//			m_Root.appendChild(child);
//			for(int i=0;i<k->seriesarr.size();i++)
//			{
//				QDomElement series=m_Doc.createElement("series");
//				child.appendChild(series);
//				amySeries* ser=k->seriesarr[i].GetPointer();
//				////////info
//				amySeriesInfo* sei=ser->info.GetPointer();
//				amyDate date=sei->date;
//				amyTime seriestime=sei->seriestime;
//				amyTime acquisitiontime=sei->acquisitiontime;
//				amySeriesInfo::ePlane plane=sei->plane;
//				DOMCTAG(series,"date",           DATE2STR(date));
//				DOMCTAG(series,"seriestime",     TIME2STR(seriestime));
//				DOMCTAG(series,"acquisitiontime",TIME2STR(acquisitiontime));
//				DOMCTAG(series,"plane",          PLANE2STR(plane));
//
//				///////patientinfo
//				if(!ser->patientinfo.IsNull())
//				{
//					QDomElement patientinfo=m_Doc.createElement("patientinfo");
//					series.appendChild(patientinfo);
//					amyPatientInfo* pinfo=ser->patientinfo.GetPointer();
//					DOMCTAG(patientinfo,"age",QString::number(pinfo->age));
//					DOMCTAG(patientinfo,"gender",pinfo->gender.c_str());
//					DOMCTAG(patientinfo,"name",pinfo->name.c_str());
//				}
//
//				//////slicearr
//				QDomElement slicearr=m_Doc.createElement("slicearr");
//				series.appendChild(slicearr);
//				for(int i=0;i<ser->slicearr.size();i++)
//				{
//					QDomElement slice=m_Doc.createElement("slice");
//					slicearr.appendChild(slice);
//
//					amySliceInfo* si=ser->slicearr[i]->info.GetPointer();
//					SATTR( filepath);
//					NATTR( imagenumber);
//					NATTR( slicelocation);
//					NATTR( slicethickness);
//					SATTR( seriesuid);
//					SATTR( seriestime);
//					NATTR( windowcenter);
//					NATTR( windowwidth);
//					NATTR( imagepositionx);
//					NATTR( imagepositiony);
//					NATTR( imagepositionz);
//				}
//				
//			}//for
//		}//case VTYPE_SERIES_SET
//		break;
//	case VTYPE_FLOAT:
//		{
//			amyFloat::Keeper f=v.Get<amyFloat>();
//			QString con=QString::number(f->value);
//			DOMTAG("content",con);
//
//		}
//		break;
//	}//switch
//}