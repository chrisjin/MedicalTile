#include"TDCalculator.h"
#include"amyAlgorithm.h"
//#include"amySubtractionAlgorithm.h"
#include"amyAlgorithmStack.h"
#include"itkImage.h"
#include"itkSubtractImageFilter.h"
#include"amyCube.h"
#include"amyDicom.h"
#include"amyTypeWrap.h"
#include"itkImageRegionConstIterator.h"
#include<sstream>
#include"amySeriesManager.h"
#include"amyAlgorithmBridge.h"
#include"amySeriesSet.h"
#include"amyArray.h"
#include"amyMatrix.h"
DLL_IMPL_BEGIN(5)
	DLL_ALGO(TDCalculator,0)
	DLL_ALGO(AvgTDCalculator,1)
	DLL_ALGO(MaxTDCalculator,2)
	DLL_ALGO(ArrayCombine,3)
	DLL_ALGO(CircleGen,4)
DLL_IMPL_END
float GetMulti(amyCube* mask,amyCube* secube,int& volume,bool& error)
{
	error=0;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;

	amyCube::tCube::Pointer psecube=secube->obj;
	amyCube::tCube::RegionType sereg=psecube->GetLargestPossibleRegion();
	amyCube::tCube::Pointer pcube=mask->obj;
	amyCube::tCube::RegionType reg=pcube->GetLargestPossibleRegion();
	if(reg!=sereg)
	{
		error=1;
		return 0;
	}
	float value=0;
	int   volumeadder=0;
	ItrType seItr(psecube,sereg);
	ItrType Itr(pcube,reg);
	for(seItr.GoToBegin(),Itr.GoToBegin();
		!seItr.IsAtEnd()&&!Itr.IsAtEnd();++seItr,++Itr)
	{
		if(Itr.Get()>0)
		{
			value+=seItr.Get();
			volumeadder++;
		}
	}
	volume=volumeadder;
	return value;
}

float GetMultiMax(amyCube* mask,amyCube* secube,bool& error)
{
	error=0;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;

	amyCube::tCube::Pointer psecube=secube->obj;
	amyCube::tCube::RegionType sereg=psecube->GetLargestPossibleRegion();
	amyCube::tCube::Pointer pcube=mask->obj;
	amyCube::tCube::RegionType reg=pcube->GetLargestPossibleRegion();
	if(reg!=sereg)
	{
		error=1;
		return 0;
	}
	float value=-1000000;
	int   volumeadder=0;
	ItrType seItr(psecube,sereg);
	ItrType Itr(pcube,reg);
	for(seItr.GoToBegin(),Itr.GoToBegin();
		!seItr.IsAtEnd()&&!Itr.IsAtEnd();++seItr,++Itr)
	{
		if(Itr.Get()>0)
		{
			if(seItr.Get()>value)
				value=seItr.Get();
		}
	}
	return value;
}
void GetMultiHistogram(amyCube* mask,amyCube* secube,vector<float>& color,vector<float>& count,bool& error)
{
	error=0;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;

	amyCube::tCube::Pointer psecube=secube->obj;
	amyCube::tCube::RegionType sereg=psecube->GetLargestPossibleRegion();
	amyCube::tCube::Pointer pcube=mask->obj;
	amyCube::tCube::RegionType reg=pcube->GetLargestPossibleRegion();
	if(reg!=sereg)
	{
		error=1;
	}
	float value=-1000000;
	int   volumeadder=0;
	ItrType seItr(psecube,sereg);
	ItrType Itr(pcube,reg);
	map<int,int> color2count;
	for(seItr.GoToBegin(),Itr.GoToBegin();
		!seItr.IsAtEnd()&&!Itr.IsAtEnd();++seItr,++Itr)
	{
		if(Itr.Get()>0)
		{
			if(color2count.find(seItr.Get())==color2count.end())
			{
				color2count[seItr.Get()]=0;
			}
			else
				color2count[seItr.Get()]++;
		}
	}
	map<int,int>::iterator itr=color2count.begin();
	for(;itr!=color2count.end();itr++)
	{
		color.push_back(itr->first);
		count.push_back(itr->second);
	}
}
void TDCalculator::Run()
{
	amyVariable vser=this->GetStack()->Pop();
	amyVariable vcub=this->GetStack()->Pop();
	if(vser.GetType()!=VTYPE_SERIES_SET&&vcub.GetType()!=VTYPE_CUBE_ARR)
		return;
	if(!vser.IsValid())
		return;
	if(!vcub.IsValid())
		return;
	FETCH(amySeriesSet,sset,vser);
	FETCH(amyCube,cube,vcub);

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"TDC");
	FETCH(amyArray,Result,ret);

	int arrsize=sset.seriesarr.size();

	for(int i=0;i<arrsize;i++)
	{
		amyCube::Keeper secube;
		secube=pSeriesManager->GetCube(sset.seriesarr[i]);
		if(secube->obj->GetLargestPossibleRegion()!=cube.obj->GetLargestPossibleRegion())
				continue;
		int dummy;
		bool error=0;
		float retv=GetMulti(&cube,secube.GetPointer(),dummy,error);
		if(error!=1)
		{
			Result().push_back(retv);
		}
	}
	this->GetStack()->Push(ret);
}

void AvgTDCalculator::Run()
{
	amyVariable vser=this->GetStack()->Pop();
	amyVariable vcub=this->GetStack()->Pop();
	if(vser.GetType()!=VTYPE_SERIES_SET&&vcub.GetType()!=VTYPE_CUBE_ARR)
		return;
	if(!vser.IsValid())
		return;
	if(!vcub.IsValid())
		return;
	FETCH(amySeriesSet,sset,vser);
	FETCH(amyCube,cube,vcub);

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"TDC");
	FETCH(amyArray,Result,ret);

	int arrsize=sset.seriesarr.size();

	for(int i=0;i<arrsize;i++)
	{
		amyCube::Keeper secube;
		secube=pSeriesManager->GetCube(sset.seriesarr[i]);
		if(secube->obj->GetLargestPossibleRegion()!=cube.obj->GetLargestPossibleRegion())
				continue;
		int volume;
		bool error=0;
		float retv=GetMulti(&cube,secube.GetPointer(),volume,error);
		if(error!=1)
		{
			Result().push_back(retv/(float)volume);
		}
	}
	this->GetStack()->Push(ret);

}

void MaxTDCalculator::Run()
{
	amyVariable vser=this->GetStack()->Pop();
	amyVariable vcub=this->GetStack()->Pop();
	if(vser.GetType()!=VTYPE_SERIES_SET&&vcub.GetType()!=VTYPE_CUBE_ARR)
		return;
	if(!vser.IsValid())
		return;
	if(!vcub.IsValid())
		return;
	FETCH(amySeriesSet,sset,vser);
	FETCH(amyCube,cube,vcub);

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"TDC");
	FETCH(amyArray,Result,ret);

	int arrsize=sset.seriesarr.size();

	for(int i=0;i<arrsize;i++)
	{
		amyCube::Keeper secube;
		secube=pSeriesManager->GetCube(sset.seriesarr[i]);
		if(secube->obj->GetLargestPossibleRegion()!=cube.obj->GetLargestPossibleRegion())
			continue;
		int dummy;
		bool error=0;
		//amyVariable ret=amyVariable::New(VTYPE_DATA_MATRIX,"TDC");
		//FETCH(amyMatrix,Result,ret);
		//amyArray& color=Result.addrow();
		//amyArray& count=Result.addrow();
		//GetMultiHistogram(&cube,secube.GetPointer(),color(),count(),error);
		//if(i>=)
		float retv=GetMultiMax(&cube,secube.GetPointer(),error);
		if(error!=1)
		{
			Result().push_back(retv);
		}
	}
	this->GetStack()->Push(ret);
}
void ArrayCombine::Run()
{
	int inputnum=this->GetStack()->GetSize();
	amyVariable ret=amyVariable::New(VTYPE_DATA_MATRIX,"data");
	FETCH(amyMatrix,mat,ret);
	for(int i=0;i<inputnum;i++)
	{
		amyVariable v=this->GetStack()->Pop();
		if(v.GetType()==VTYPE_DATA_ARRAY)
		{
			FETCH(amyArray,ori,v);
			amyArray& arr=mat.addrow();
			for(int j=0;j<ori.size();j++)
			{
				arr().push_back(ori[j]);
			}
		}
		else if(v.GetType()==VTYPE_DATA_MATRIX)
		{
			FETCH(amyMatrix,orimat,v);
			for(int j=0;j<orimat.rowcount();j++)
			{
				amyArray& ori=orimat[j];
				amyArray& arr=mat.addrow();
				for(int k=0;k<ori.size();k++)
				{
					arr().push_back(ori[k]);
				}
			}
		}
	
	}
	this->GetStack()->Push(ret);
}


void   CircleGen::Run()
{
	amyVariable ret=amyVariable::New(VTYPE_DATA_MATRIX,"Cir");
	FETCH(amyMatrix,mat,ret);
	amyArray& xarr=mat.addrow();
	amyArray& yarr=mat.addrow();
	for(int i=0;i<90;i++)
	{
		
		float x=sin(4*(float)i/180.0*3.1415926)*20;
		float y=cos(4*(float)i/180.0*3.1415926)*20;
		xarr().push_back(x);
		yarr().push_back(y);
	}
	this->GetStack()->Push(ret);
}