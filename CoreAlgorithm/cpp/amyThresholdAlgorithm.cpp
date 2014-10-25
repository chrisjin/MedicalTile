#include"amyThresholdAlgorithm.h"
#include"amyAlgorithmStack.h"
#include"itkImage.h"
#include"itkOtsuThresholdImageFilter.h"
#include"amyCube.h"
#include"itkRegionOfInterestImageFilter.h"
#include"itkImageRegionIterator.h"

void amyThresholdAlgorithm::Run()
{
	
	amyAlgorithmStack* stack=this->GetStack();
	amyVariable v1=stack->Pop();
	if(v1.GetType()!=VTYPE_CUBE)
		return;
	amyCube::Keeper cube1=v1.Get<amyCube>();

	typedef itk::RegionOfInterestImageFilter<amyCube::tCube,amyCube::tCube> ROIType;
	ROIType::Pointer rf=ROIType::New();
	rf->SetInput(cube1->obj);
	rf->SetRegionOfInterest(cube1->obj->GetRequestedRegion());
	rf->Update();
	typedef itk::OtsuThresholdImageFilter<amyCube::tCube,amyCube::tCube> ThresholdType;
	ThresholdType::Pointer threshold=ThresholdType::New();
	threshold->SetInput(rf->GetOutput());
	threshold->SetOutsideValue(400);
	threshold->SetInsideValue(-400);
	threshold->SetNumberOfHistogramBins(255);
	threshold->SetAutoMinimumMaximum(1);
	threshold->Update();
	amyCube::tCube::PixelType th=threshold->GetThreshold();

	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
	retcube->SetRegions(cube1->obj->GetLargestPossibleRegion());
	retcube->SetSpacing(cube1->obj->GetSpacing());
	retcube->SetDirection(cube1->obj->GetDirection());
	retcube->Allocate();
	typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;
	ItrType Itri(cube1->obj,cube1->obj->GetLargestPossibleRegion());
	ItrType Itro(retcube,retcube->GetLargestPossibleRegion());
	for(Itri.GoToBegin(),Itro.GoToBegin();!Itri.IsAtEnd()&&!Itro.IsAtEnd();++Itri,++Itro)
	{
		amyCube::tCube::PixelType v=Itri.Get();
		if(v>=th)
		{
			Itro.Set(400);
		}
		else
		{
			Itro.Set(-400);
		}
	}
	
	
	amyVariable v3=amyVariable::New(VTYPE_CUBE,"Ret");
	amyCube::Keeper cube3=v3.Get<amyCube>();
	cube3->SetObj(retcube);
	stack->Push(v3);
}