#include"VarPlot.h"
#include"amySeriesSet.h"
#include"amyCube.h"
#include"amyAlgorithmStack.h"
#include"itkImageRegionIterator.h"
#include"amySeriesManager.h"
#include"amyAlgorithmProgress.h"
#include"itkDiscreteGaussianImageFilter.h"
#include"itkMeanImageFilter.h"
#include"itkMedianImageFilter.h"
float CalVar(vector<int>& a)
{
	float mean=0;
	float sum=0;
	float num=0;
	for(int i=0;i<a.size();i++)
	{
		sum+=a[i];
		num++;
	}
	mean=sum/num;
	
	float var=0;
	for(int i=0;i<a.size();i++)
	{
		var+=(a[i]-mean)*(a[i]-mean);
	}

	int peak;
	int com=-1;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]>com)
		{
			com=a[i];
			peak=i;
		}
	}
	int peaknum=com;
	int ret;
	for(int i=peak;i<a.size();i++)
	{
		if(a[i]<com)
		{
			com=a[i];
			ret=com;
		}
	}
	int valnum=com;
	return double(peaknum)/double(valnum);
}
void   VarPlot::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	FETCH(amySeriesSet,set,v1);
	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);

	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
	retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
	retcube->SetSpacing(cubeobj->obj->GetSpacing());
	retcube->Allocate();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
	vector<CItrType> ItrArr;
	vector<amyCube::Keeper> PreventFromReleasing;
	vector<amyCube::tCube::Pointer> Fuck;
	typedef itk::MeanImageFilter<amyCube::tCube,amyCube::tCube> GF;
	for(int i=0;i<set.seriesarr.size();i++)
	{
		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
		PreventFromReleasing.push_back(kcube);
		ItrArr.push_back(CItrType(kcube->obj,kcube->obj->GetLargestPossibleRegion()));
		
		//GF::Pointer f=GF::New();
		//f->SetInput(kcube->obj);
		//amyCube::tCube::SizeType size;
		//size[0]=1;
		//size[1]=1;
		//size[2]=1;
		//f->SetRadius(size);
		//f->Update();
		//Fuck.push_back(f->GetOutput());
		//ItrArr.push_back(CItrType(f->GetOutput(),f->GetOutput()->GetLargestPossibleRegion()));
	}
	
	
	
	ItrType ItrRet(retcube,retcube->GetLargestPossibleRegion());
	while(1)
	{
		if(ItrRet.IsAtEnd())
			break;
		vector<int>  arrforonepixel;
		for(int i=0;i<ItrArr.size();i++)
		{
			arrforonepixel.push_back(ItrArr[i].Get());
		}
		int peak;
		int set=CalVar(arrforonepixel);
		ItrRet.Set(set);
		for(int i=0;i<ItrArr.size();i++)
		{
			++ItrArr[i];
		}
		++ItrRet;
	}

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Peak");
	FETCH(amyCube,ccc,ret);
	ccc.SetObj(retcube);
	this->GetStack()->Push(ret);
}