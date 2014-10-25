#include"amyDICOMFolder.h"
#include"amyDICOM.h"
#include<algorithm>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dctk.h>
#include"amyDebug.h"
#include"amyTypeWrap.h"
#include<string>
#include"amyUtil.h"
#include"amySeriesSet.h"
using namespace std;
bool SliceCompare(amySlice::Keeper a,amySlice::Keeper b)
{
	if(a->info->seriesuid<b->info->seriesuid)
		return true;
	else if (a->info->seriesuid>b->info->seriesuid)
		return false;
	else if(a->info->seriestime<b->info->seriestime)
		return true;
	else if(a->info->seriestime>b->info->seriestime)
		return false;
	int result = a->info->imagenumber - b->info->imagenumber;
	return result< 0 ? true : false;
}
bool CheckString(string a,string b)////将文件名相同的前段和相同的后段去掉 只留下不同的部分
{
	char namea[255],nameb[255];
	strcpy(namea,a.c_str());
	strcpy(nameb,b.c_str());
	int la=strlen(namea);
	int lb=strlen(nameb);
	for(int i=la-1,j=lb-1;i>=0&&j>=0;i--,j--)
	{
		if(namea[i]==nameb[j])
		{
			namea[i]=0;
			nameb[j]=0;
		}
		else
		{
			break;
		}
	}
	int posa=0;
	int posb=0;
	for(int i=0,j=0;i<la,j<lb;i++,j++)
	{
		if(namea[i]!=nameb[j])
		{
			posa=i;
			posb=j;
			break;
		}
	}
	char* newa=namea+posa;
	char* newb=nameb+posb;
	return atoi(newa)<atoi(newb)?1:0;
}
bool SliceLocationCompare(amySlice::Keeper a,amySlice::Keeper b)
{
	if(a->info->slicelocation < b->info->slicelocation)
		return true;
    else if(a->info->slicelocation > b->info->slicelocation)
	    return false;
	return CheckString(a->info->filepath,b->info->filepath);  ///SliceLocation不能正常获取情况下靠 文件名排序
}
bool SeriesTimeCompare(amySeries::Keeper a,amySeries::Keeper b)
{
	amyDate d1=
		a->info->date;
	amyDate d2=
		b->info->date;
	amyTime t1=
		a->info->acquisitiontime;
	amyTime t2=
		b->info->acquisitiontime;
	amyTime tt1=
		a->info->seriestime;
	amyTime tt2=
		b->info->seriestime;
	if(d1<d2)
		return 1;
	else if(d1==d2)
	{
		if(t1<t2)
			return 1;
		else if(t1==t2)
		{
			if(tt1<tt2)
				return 1;
			else if(tt1==tt2)
			{
				if(a->slicearr.size()>0&&b->slicearr.size()>0)
				{
					return a->slicearr[0]->info->imagenumber<b->slicearr[0]->info->imagenumber;
				}
			}
		}
	}
	return 0;
}
void amySeriesSplitter::Sort()
{
	std::sort(this->m_SliceArr.begin(),this->m_SliceArr.end(),SliceCompare);
}

void amySeriesSplitter::AddSlice(amyKeeper<amySlice> slice)
{
	m_SliceArr.push_back(slice);
}
amySeriesSplitter::amySeriesSplitter()
{
	Reset();
}
void amySeriesSplitter::Reset()
{
	m_SliceArr.clear();
	CurrentPos=0;
	CurrentPosInSubSer=0;
	Thickness=0;
	SpaceBtw=0;
	CurrentSubseries=0;
}

amySeries* amySeriesSplitter::NextSeries()
{

#define STEPINSUBSER \
	{CurrentSubseries->slicearr.push_back(this->m_SliceArr[CurrentPos]);CurrentPosInSubSer++;CurrentPos++;}
#define LOCATIONDIF\
	(fabs(this->m_SliceArr[CurrentPos]->info->slicelocation-this->m_SliceArr[CurrentPos-1]->info->slicelocation))
#define NUMDIF\
	(this->m_SliceArr[CurrentPos]->info->imagenumber-this->m_SliceArr[CurrentPos-1]->info->imagenumber)
#define SERIESUID_SAME (this->m_SliceArr[CurrentPos]->info->seriesuid==this->m_SliceArr[CurrentPos-1]->info->seriesuid)
	while(1)
	{
		if(CurrentPos==this->m_SliceArr.size())
		{
			CurrentPos++;
			goto FOUND;
		}
		if(CurrentPos>this->m_SliceArr.size())
		{
			goto END;
		}
		if(CurrentPosInSubSer==0)
		{
			Thickness=this->m_SliceArr[CurrentPos]->info->slicethickness;
			CurrentSubseries=new amySeries;
			STEPINSUBSER
				continue;
		}
		if(CurrentPosInSubSer==1)
		{
			if(fabs(this->m_SliceArr[CurrentPos]->info->slicethickness-Thickness)<=0.1)
			{
				if(NUMDIF)
					SpaceBtw=LOCATIONDIF/NUMDIF;
				else
					SpaceBtw=LOCATIONDIF;
				STEPINSUBSER
					continue;
			}
			else
			{
				goto FOUND;
			}
		}
		if(CurrentPosInSubSer>=2)
		{
			float spcbtw;
			if(NUMDIF)
				spcbtw=LOCATIONDIF/NUMDIF;
			else
				spcbtw=LOCATIONDIF;
			if(!SERIESUID_SAME)
			{
				goto FOUND;
			}
			else if(fabs(spcbtw-SpaceBtw)<=0.1)
			{
				STEPINSUBSER
					continue;
			}
			else
			{
				goto FOUND;
			}
		}
	}
FOUND:
	CurrentPosInSubSer=0;
	return CurrentSubseries;
END:
	CurrentPos=0;
	CurrentPosInSubSer=0;
	CurrentSubseries=0;
	return 0;
}

//void amyPatientSplitter::Sort()
//{
//	std::sort(this->m_SliceArr.begin(),this->m_SliceArr.end(),SliceCompare);
//}
//void amyPatientSplitter::Reset()
//{
//
//}
//void amyPatientSplitter::AddSlice(amySlice* slice)
//{
//	this->m_SliceArr.push_back(slice);
//}



void amyDCMFolder::OnFindFile(const char* name)
{
	DcmFileFormat Format;
	OFCondition status=Format.loadFile(name);
	string PatientName;
	string SeriesUID;
	if(status.good())
	{
		amySlice::Keeper newinfo=amySlice::New();
		OFString str;
		newinfo->info->filepath=name;
		if (Format.getDataset()->findAndGetOFString(DCM_InstanceNumber, str).good())
		{
			newinfo->info->imagenumber=atoi(str.c_str());
		}
		if (Format.getDataset()->findAndGetOFString(DCM_SliceLocation, str).good())
		{
			newinfo->info->slicelocation=atof(str.c_str());
		}
		else
		{
			newinfo->info->slicelocation=0;
		}
		if (Format.getDataset()->findAndGetOFString(DCM_SeriesTime, str).good())
		{
			newinfo->info->seriestime=str.c_str();
		}
		if (Format.getDataset()->findAndGetOFString(DCM_SliceThickness, str).good())
		{
			newinfo->info->slicethickness=atof(str.c_str());
		}
		else
		{
			newinfo->info->slicethickness=0;
		}
		if (Format.getDataset()->findAndGetOFString(DCM_PatientName, str).good())
		{
			PatientName=str.c_str();
		}
		if (Format.getDataset()->findAndGetOFString(DCM_PatientID, str).good())//某些dicom图像ID和NAME是一样的某一些则不一样
		{
			int pos=PatientName.find(str.c_str());
			if(pos==-1)
			{
				PatientName=PatientName+str.c_str();
			}
		}
		if (Format.getDataset()->findAndGetOFString(DCM_SeriesInstanceUID, str).good())
		{
			newinfo->info->seriesuid=str.c_str();
		}
		if (Format.getDataset()->findAndGetOFString(DCM_WindowWidth, str).good())
		{
			newinfo->info->windowwidth=atoi(str.c_str());
		}
		if (Format.getDataset()->findAndGetOFString(DCM_WindowCenter, str).good())
		{
			newinfo->info->windowcenter=atoi(str.c_str());
		}
		if (Format.getDataset()->findAndGetOFString(DCM_ImagePositionPatient, str,0).good())
		{
			newinfo->info->imagepositionx=atof(str.c_str());
		}
		if (Format.getDataset()->findAndGetOFString(DCM_ImagePositionPatient, str,1).good())
		{
			newinfo->info->imagepositiony=atof(str.c_str());
		}
		if (Format.getDataset()->findAndGetOFString(DCM_ImagePositionPatient, str,2).good())
		{
			newinfo->info->imagepositionz=atof(str.c_str());
		}
		amySeriesSplitter* Splitter;
		map<string,amySeriesSplitter*>::iterator itr=m_Name2Splitter.find(PatientName);
		if(itr==m_Name2Splitter.end())
		{
			Splitter=new amySeriesSplitter;
			m_Name2Splitter[PatientName]=Splitter;
			amyPatient *p=new amyPatient;
			p->info->name=PatientName;
			if (Format.getDataset()->findAndGetOFString(DCM_PatientSex, str).good())
			{
				p->info->gender=str.c_str();
			}
			if (Format.getDataset()->findAndGetOFString(DCM_PatientAge, str).good())
			{
				p->info->age=atoi(str.c_str());
			}
			m_PatientArr.push_back(p);
			m_SplitterArr.push_back(Splitter);
		}
		else
		{
			Splitter=itr->second;
		}
		if(Splitter)
		{
			Splitter->AddSlice(newinfo);
		}
		Format.clear();
	}
	else
	{
		//amyWarn(name);
	}
}

void amyDCMFolder::Parse()
{
	for(int i=0;i<m_PatientArr.size();i++)
	{
		m_SplitterArr[i]->Sort();
		while(1)
		{
			amySeries* ser=m_SplitterArr[i]->NextSeries();
			if(ser==0)
				break;
			else
			{
				m_PatientArr[i]->seriesarr.push_back(ser);
				ser->patientinfo=m_PatientArr[i]->info;
				//ser->date=ser->slicearr[0]->seriestime;
			}
		}
	}
	for(int i=0;i<m_PatientArr.size();i++)
	{
		for(int j=0;j<m_PatientArr[i]->seriesarr.size();j++)
		{
			amyKeeper<amySeries> ser=m_PatientArr[i]->seriesarr[j];

			std::sort(ser->slicearr.begin(),ser->slicearr.end(),SliceLocationCompare);
			amySlice::Keeper slice=ser->slicearr[0];
			ser->info->seriestime=slice->info->seriestime.c_str();
			
			DcmFileFormat Format;
			OFCondition status=Format.loadFile(slice->info->filepath.c_str());
			if(status.good())
			{
				OFString str;
				if (Format.getDataset()->findAndGetOFString(DCM_AcquisitionTime,str).good())
				{
					ser->info->acquisitiontime=str.c_str();
				}
				if (Format.getDataset()->findAndGetOFString(DCM_SeriesDate,str).good())
				{
					ser->info->date=str.c_str();
				}
				
			}

			if(ser->slicearr.size()>=2)
			{
				float dx=fabs(ser->slicearr[0]->info->imagepositionx-ser->slicearr[1]->info->imagepositionx);
				float dy=fabs(ser->slicearr[0]->info->imagepositiony-ser->slicearr[1]->info->imagepositiony);
				float dz=fabs(ser->slicearr[0]->info->imagepositionz-ser->slicearr[1]->info->imagepositionz);
				if(dy<=0.1&&dz<=0.1)
				{
					ser->info->plane=amySeriesInfo::SAGITTAL;
				}
				else if(dx<=0.1&&dz<=0.1)
				{
					ser->info->plane=amySeriesInfo::CORONAL;
				}
				else if(dx<=0.1&&dy<=0.1)
				{
					ser->info->plane=amySeriesInfo::AXIAL;
				}
				else
				{
					ser->info->plane=amySeriesInfo::UNKNOWN;
				}
			}
		}
	}
	for(int i=0;i<m_SplitterArr.size();i++)
	{
		if(m_SplitterArr[i])
			delete m_SplitterArr[i];
	}
	m_SplitterArr.clear();
	m_Name2Splitter.clear();
	
}

void amyDCMFolder::InsertSeriesSet(amyKeeper<amySeriesSet> sst)
{
	if(sst->seriesarr.size()==0)
		return;
	string pname=sst->seriesarr[0]->patientinfo->name;
	amyPatient::Keeper kp;
	for(int i=0;i<this->m_PatientArr.size();i++)
	{
		if(this->m_PatientArr[i]->info->name==pname)
		{
			kp=this->m_PatientArr[i];
		}
	}
	if(kp.IsNull())
	{
		kp=amyUtil::MakePatientFromSeriesSet(sst);
		this->m_PatientArr.push_back(kp);
	}
	else
	{
		if(kp->seriesarr.size()>0)
		{
			vector<amySeries::Keeper> newseriesarr;
			for(int i=0;i<kp->seriesarr.size();i++)
			{
					newseriesarr.push_back(kp->seriesarr[i]);
			}
			for(int i=0;i<sst->seriesarr.size();i++)
			{
				int flag=0;   //避免重复
				for(int j=0;j<kp->seriesarr.size();j++)
				{
					if(kp->seriesarr[j]==sst->seriesarr[i])
						flag=1;
					//newseriesarr.push_back(kp->seriesarr[j]);
				}
				if(flag==0)
					newseriesarr.push_back(sst->seriesarr[i]);
			}
			std::sort(newseriesarr.begin(),newseriesarr.end(),SeriesTimeCompare);
			kp->seriesarr=newseriesarr;
		}//if(kp->seriesarr.size()>0)
	}//if(kp.IsNull())else
}