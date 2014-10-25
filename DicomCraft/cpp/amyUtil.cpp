#include"amyUtil.h"
#include<math.h>
#include<stdlib.h>
#include"amyDICOM.h"
#include"amyCube.h"
#include"itkImage.h"
#include"itkImageRegionConstIterator.h"
#include"itkConstSliceIterator.h"
#include"amyTypeWrap.h"
#include"amySeriesSet.h"
namespace amyUtil
{

void   GetWindowCenterWidth(amyCube* cube,int& c,int &w)
{
	int min=1000000;
	int max=-1000000;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItType;
	ItType itr( cube->obj, cube->obj->GetRequestedRegion() );
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		short v=itr.Get();
		if(v<min)
			min=v;
		if(v>max)
			max=v;
	}
	c=(max+min-0.5)/2;
	w=max-min;
}

void    GetCubeMinMax(amyCube* cube,int& min,int& max)
{
	min=1000000;
	max=-1000000;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItType;
	ItType itr( cube->obj, cube->obj->GetLargestPossibleRegion());
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		amyCube::tCube::PixelType v=itr.Get();
		if(v<min)
			min=v;
		if(v>max)
			max=v;
	}

}
void    GetCubeMinMax(amyCube* cube,int slice,int& min,int& max)
{
	amyCube::tCube::RegionType r=cube->obj->GetLargestPossibleRegion();
	amyCube::tCube::SizeType   s=r.GetSize();
	amyCube::tCube::IndexType  in=r.GetIndex();
	if(slice>=s[2])
		slice=s[2]-1;
	if(slice<0)
		slice=0;
	s[2]=1;
	in[2]=slice;
	r.SetIndex(in);
	r.SetSize(s);
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItType;
	ItType itr( cube->obj, r);
	min=1000000;
	max=-1000000;
	for(itr.GoToBegin();!itr.IsAtEnd();++itr)
	{
		amyCube::tCube::PixelType v=itr.Get();
		if(v<min)
			min=v;
		if(v>max)
			max=v;
	}
}

ePlane GetPlaneType(amyCube* cube)
{
	amyCube::tCube::DirectionType d=cube->obj->GetDirection();
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			if(fabs(fabs(d[i][j])-1)<0.1)
				d[i][j]=1;
			else
				d[i][j]=0;
		}
	if(d[0][0]==1&&d[1][2]==1&&d[2][1]==1)
		return CORONAL;
	else if(d[0][0]==1&&d[1][1]==1&&d[2][2]==1)
		return AXIAL;
	else if(d[0][2]==1&&d[1][0]==1&&d[2][1]==1)
		return SAGITTAL;
	else 
		return UNKNOWN;
}


IMPLEMENT_SINGLETON(Lock)
Lock::Lock()
{
	InitializeCriticalSection(&m_Cs);
}
void Lock::EnterCritical()
{
	EnterCriticalSection(&m_Cs);
}
void Lock::LeaveCritical()
{
	LeaveCriticalSection(&m_Cs);
}

amyKeeper<amyPatient> MakePatientFromSeriesSet(amyKeeper<amySeriesSet> ser)
{
	amyKeeper<amyPatient> pp=amyPatient::New();
	if(ser->seriesarr.size()>0)
	{
		if(!ser->seriesarr[0]->patientinfo.IsNull())
		{
			pp->info=ser->seriesarr[0]->patientinfo;
		}
	}
	for(int i=0;i<ser->seriesarr.size();i++)
	{
		if(!ser->seriesarr[i].IsNull())
		{
			pp->seriesarr.push_back(ser->seriesarr[i]);
		}
	}
	return pp;
}
}//namespace