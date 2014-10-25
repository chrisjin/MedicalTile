#include"MaskHistogram.h"
#include"amyCube.h"
#include"amyMatrix.h"
#include"itkImageRegionConstIterator.h"
#include"amyAlgorithmStack.h"
#include"itkHistogram.h"
#include"itkOtsuMultipleThresholdsCalculator.h"
#include"amyNumber.h"
#include"itkImageRegionIterator.h"
void   MaskHistogram::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();

	FETCH(amyCube,cube,v1);
	FETCH(amyCube,mask,v2);

	int min=SHRT_MAX;
	int max=-SHRT_MAX;
	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	CItrType Itrcube(cube.obj,cube.obj->GetLargestPossibleRegion());
	CItrType Itrmask(mask.obj,mask.obj->GetLargestPossibleRegion());

	for(Itrcube.GoToBegin(),Itrmask.GoToBegin();
		!Itrcube.IsAtEnd()&&!Itrmask.IsAtEnd();
		++Itrcube,++Itrmask)
	{
		if(Itrmask.Get()>0)
		{
			if(Itrcube.Get()>max)
			{
				max=Itrcube.Get();
			}
			if(Itrcube.Get()<min)
			{
				min=Itrcube.Get();
			}
		}
	}

	typedef int MeasurementType;
	typedef itk::Statistics::SparseFrequencyContainer2 FrequencyContainerType;
	typedef FrequencyContainerType::AbsoluteFrequencyType FrequencyType;
	typedef itk::Statistics::Histogram<MeasurementType,FrequencyContainerType> HistogramType;

	const unsigned int numberOfComponents = 1;

	HistogramType::Pointer histo=HistogramType::New();
	histo->SetMeasurementVectorSize(numberOfComponents);

	HistogramType::SizeType size(numberOfComponents);
	size.fill(max-min+1);

	HistogramType::MeasurementVectorType lowerBound( numberOfComponents );
	HistogramType::MeasurementVectorType upperBound( numberOfComponents );
	lowerBound[0] =min;
	upperBound[0] =max;

	histo->Initialize(size, lowerBound, upperBound );



	for(Itrcube.GoToBegin(),Itrmask.GoToBegin();
		!Itrcube.IsAtEnd()&&!Itrmask.IsAtEnd();
		++Itrcube,++Itrmask)
	{
		if(Itrmask.Get()>0)
		{
			HistogramType::MeasurementVectorType index( numberOfComponents );
			index[0]=Itrcube.Get();
			//HistogramType::
			histo->IncreaseFrequency(histo->GetInstanceIdentifier(histo->GetIndex(index)),1);
		}
	}

	//typedef itk::OtsuMultipleThresholdsCalculator<HistogramType> CalType;
	//CalType::Pointer cal = CalType::New();
	//cal->SetNumberOfThresholds(2);
	//cal->SetInputHistogram(histo);
	//cal->Update();

	//amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"tre");
	//FETCH(amyArray,retarr,ret);

	//int lowthreshold=cal->GetOutput()[0];
	//int highthreshold=cal->GetOutput()[1];
	//retarr().push_back(lowthreshold);
	//retarr().push_back(highthreshold);

	
	amyVariable ret=amyVariable::New(VTYPE_DATA_MATRIX,"tre");
	FETCH(amyMatrix,retmat,ret);
	amyArray& xa=retmat.addrow();
	amyArray& ya=retmat.addrow();

	HistogramType::ConstIterator hisitr=histo->Begin();
	for(;histo->End()!=hisitr;++hisitr)
	{
		xa().push_back(hisitr.GetMeasurementVector()[0]);
		ya().push_back(hisitr.GetFrequency());
	}
	
	this->GetStack()->Push(ret);



	//amyVariable ret1=amyVariable::New(VTYPE_CUBE,"ret1");
	//amyVariable ret2=amyVariable::New(VTYPE_CUBE,"ret2");
	//amyVariable ret3=amyVariable::New(VTYPE_CUBE,"ret3");

	//FETCH(amyCube,retcube1,ret1);
	//FETCH(amyCube,retcube2,ret2);
	//FETCH(amyCube,retcube3,ret3);

	//amyCube::tCube::Pointer retobj1=amyCube::tCube::New();
	//amyCube::tCube::Pointer retobj2=amyCube::tCube::New();
	//amyCube::tCube::Pointer retobj3=amyCube::tCube::New();


	//retobj1->SetSpacing(cube.obj->GetSpacing());
	//retobj2->SetSpacing(cube.obj->GetSpacing());
	//retobj3->SetSpacing(cube.obj->GetSpacing());

	//retobj1->SetRegions(cube.obj->GetLargestPossibleRegion());
	//retobj2->SetRegions(cube.obj->GetLargestPossibleRegion());
	//retobj3->SetRegions(cube.obj->GetLargestPossibleRegion());

	//retobj1->SetDirection(cube.obj->GetDirection());
	//retobj2->SetDirection(cube.obj->GetDirection());
	//retobj3->SetDirection(cube.obj->GetDirection());

	//retobj1->Allocate();
	//retobj2->Allocate();
	//retobj3->Allocate();

	//typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;

	//ItrType Itrret1(retobj1,retobj1->GetLargestPossibleRegion());
	//ItrType Itrret2(retobj2,retobj2->GetLargestPossibleRegion());
	//ItrType Itrret3(retobj3,retobj3->GetLargestPossibleRegion());

	//for(Itrret1.GoToBegin(),Itrret2.GoToBegin(),Itrret3.GoToBegin(),Itrcube.GoToBegin(),Itrmask.GoToBegin();
	//	!Itrret1.IsAtEnd()&&!Itrret2.IsAtEnd()&&!Itrret3.IsAtEnd()&&!Itrcube.IsAtEnd()&&!Itrmask.IsAtEnd();
	//	++Itrret1,++Itrret2,++Itrret3,++Itrcube,++Itrmask)
	//{
	//	if(Itrmask.Get()>0)
	//	{
	//		if(Itrcube.Get()<lowthreshold)
	//		{
	//			Itrret1.Set(400);
	//			Itrret2.Set(-400);
	//			Itrret3.Set(-400);
	//		}
	//		else if(Itrcube.Get()>=lowthreshold&&Itrcube.Get()<highthreshold)
	//		{
	//			Itrret1.Set(-400);
	//			Itrret2.Set(400);
	//			Itrret3.Set(-400);
	//		}
	//		else
	//		{
	//			Itrret1.Set(-400);
	//			Itrret2.Set(-400);
	//			Itrret3.Set(400);
	//		}
	//	}
	//	else//if(Itrmask.Get()>0)
	//	{
	//		Itrret1.Set(-400);
	//		Itrret2.Set(-400);
	//		Itrret3.Set(-400);
	//	}
	//}
	//
	//retcube1.SetObj(retobj1);
	//retcube2.SetObj(retobj2);
	//retcube3.SetObj(retobj3);
	//this->GetStack()->Push(ret1);
	//this->GetStack()->Push(ret2);
	//this->GetStack()->Push(ret3);
}


void OtsuMultiSeg::Run()
{
	vector<amyVariable> vararr;
	this->GetStack()->Top(vararr,2);
	FETCH(amyCube,cube,vararr[0]);
	FETCH(amyCube,mask,vararr[1]);

	MaskHistogram calhisto;
	calhisto.Run();

	amyVariable v=this->GetStack()->Pop();
	FETCH(amyMatrix,histmat,v);
	int row=histmat.rowcount();

	amyArray& xarr=histmat[0];
	amyArray& yarr=histmat[1];

	int min=xarr[0];
	int max=xarr[xarr.size()-1];


	
	typedef int MeasurementType;
	typedef itk::Statistics::SparseFrequencyContainer2 FrequencyContainerType;
	typedef FrequencyContainerType::AbsoluteFrequencyType FrequencyType;
	typedef itk::Statistics::Histogram<MeasurementType,FrequencyContainerType> HistogramType;

	const unsigned int numberOfComponents = 1;

	HistogramType::Pointer histo=HistogramType::New();
	histo->SetMeasurementVectorSize(numberOfComponents);

	HistogramType::SizeType size(numberOfComponents);
	size.fill(max-min+1);

	HistogramType::MeasurementVectorType lowerBound( numberOfComponents );
	HistogramType::MeasurementVectorType upperBound( numberOfComponents );
	lowerBound[0] =min;
	upperBound[0] =max;

	histo->Initialize(size, lowerBound, upperBound );

	for(int i=0;i<yarr.size();i++)
	{
		histo->SetFrequency(histo->GetInstanceIdentifier(histo->GetIndex(xarr[i])),yarr[i]);
	}


	
	typedef itk::OtsuMultipleThresholdsCalculator<HistogramType> CalType;
	CalType::Pointer cal = CalType::New();
	cal->SetNumberOfThresholds(2);
	cal->SetInputHistogram(histo);
	cal->Update();

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"tre");
	FETCH(amyArray,retarr,ret);

	int lowthreshold=cal->GetOutput()[0];
	int highthreshold=cal->GetOutput()[1];
	retarr().push_back(lowthreshold);
	retarr().push_back(highthreshold);
	this->GetStack()->Push(ret);


	
	amyVariable ret1=amyVariable::New(VTYPE_CUBE,"ret1");
	amyVariable ret2=amyVariable::New(VTYPE_CUBE,"ret2");
	amyVariable ret3=amyVariable::New(VTYPE_CUBE,"ret3");

	FETCH(amyCube,retcube1,ret1);
	FETCH(amyCube,retcube2,ret2);
	FETCH(amyCube,retcube3,ret3);

	amyCube::tCube::Pointer retobj1=amyCube::tCube::New();
	amyCube::tCube::Pointer retobj2=amyCube::tCube::New();
	amyCube::tCube::Pointer retobj3=amyCube::tCube::New();


	retobj1->SetSpacing(cube.obj->GetSpacing());
	retobj2->SetSpacing(cube.obj->GetSpacing());
	retobj3->SetSpacing(cube.obj->GetSpacing());

	retobj1->SetRegions(cube.obj->GetLargestPossibleRegion());
	retobj2->SetRegions(cube.obj->GetLargestPossibleRegion());
	retobj3->SetRegions(cube.obj->GetLargestPossibleRegion());

	retobj1->SetDirection(cube.obj->GetDirection());
	retobj2->SetDirection(cube.obj->GetDirection());
	retobj3->SetDirection(cube.obj->GetDirection());

	retobj1->Allocate();
	retobj2->Allocate();
	retobj3->Allocate();

	typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;

	ItrType Itrret1(retobj1,retobj1->GetLargestPossibleRegion());
	ItrType Itrret2(retobj2,retobj2->GetLargestPossibleRegion());
	ItrType Itrret3(retobj3,retobj3->GetLargestPossibleRegion());

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	CItrType Itrcube(cube.obj,cube.obj->GetLargestPossibleRegion());
	CItrType Itrmask(mask.obj,mask.obj->GetLargestPossibleRegion());
	
	for(Itrret1.GoToBegin(),Itrret2.GoToBegin(),Itrret3.GoToBegin(),Itrcube.GoToBegin(),Itrmask.GoToBegin();
		!Itrret1.IsAtEnd()&&!Itrret2.IsAtEnd()&&!Itrret3.IsAtEnd()&&!Itrcube.IsAtEnd()&&!Itrmask.IsAtEnd();
		++Itrret1,++Itrret2,++Itrret3,++Itrcube,++Itrmask)
	{
		if(Itrmask.Get()>0)
		{
			if(Itrcube.Get()<lowthreshold)
			{
				Itrret1.Set(400);
				Itrret2.Set(-400);
				Itrret3.Set(-400);
			}
			else if(Itrcube.Get()>=lowthreshold&&Itrcube.Get()<highthreshold)
			{
				Itrret1.Set(-400);
				Itrret2.Set(400);
				Itrret3.Set(-400);
			}
			else
			{
				Itrret1.Set(-400);
				Itrret2.Set(-400);
				Itrret3.Set(400);
			}
		}
		else//if(Itrmask.Get()>0)
		{
			Itrret1.Set(-400);
			Itrret2.Set(-400);
			Itrret3.Set(-400);
		}
	}
	
	retcube1.SetObj(retobj1);
	retcube2.SetObj(retobj2);
	retcube3.SetObj(retobj3);
	this->GetStack()->Push(ret1);
	this->GetStack()->Push(ret2);
	this->GetStack()->Push(ret3);

}