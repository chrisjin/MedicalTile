#include"LargestComponent.h"
#include"amyCube.h"
#include"itkConnectedComponentImageFilter.h"
#include"amyAlgorithmStack.h"
#include"itkImageRegionConstIterator.h"
#include"itkImageRegionIterator.h"
#include"itkRescaleIntensityImageFilter.h"
void LargestComponent::Run()
{
	amyCube::Keeper c1=this->GetStack()->Pop().Get<amyCube>();


	typedef itk::RescaleIntensityImageFilter< amyCube::tCube, amyCube::tCube > RescaleFilterType;
	RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
	rescaleFilter->SetOutputMinimum(0);
	rescaleFilter->SetOutputMaximum(itk::NumericTraits<amyCube::tCube::PixelType>::max());
	rescaleFilter->SetInput(c1->obj);
	rescaleFilter->Update();

	typedef itk::ConnectedComponentImageFilter <amyCube::tCube, amyCube::tCube>
    ConnectedComponentImageFilterType;
	ConnectedComponentImageFilterType::Pointer filter=ConnectedComponentImageFilterType::New();
	filter->SetInput(rescaleFilter->GetOutput());
	filter->Update();

	amyCube::tCube::Pointer labelimage=filter->GetOutput();
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ConstCubeIteratorType;
	typedef itk::ImageRegionIterator<amyCube::tCube> CubeIteratorType;
	int* histogram=(int*)malloc(sizeof(int)*1000);
	memset(histogram,0,sizeof(int)*1000);
	ConstCubeIteratorType iItr(c1->obj,c1->obj->GetLargestPossibleRegion());
	ConstCubeIteratorType labelItr(labelimage,labelimage->GetLargestPossibleRegion());
	for(iItr.GoToBegin(),labelItr.GoToBegin();
		!iItr.IsAtEnd()&&!labelItr.IsAtEnd();
		++iItr,++labelItr)
	{
		int index=labelItr.Get();
		int v=iItr.Get();
		if(index>=0&&v>10)
		histogram[index]++;
	}

	int basevalue=0;
	int gray=0;
	for(int i=0;i<1000;i++)
	{
		if(histogram[i]>basevalue)
		{
			basevalue=histogram[i];
			gray=i;
		}
	}
	amyCube::tCube::Pointer ret=amyCube::tCube::New();
	ret->SetSpacing(c1->obj->GetSpacing());
	ret->SetRegions(c1->obj->GetLargestPossibleRegion());
	ret->Allocate();
	stringstream ss;
	ss<<gray;
	//MessageBox(0,ss.str().c_str(),0,MB_OK);
	
	CubeIteratorType  oItr(ret,ret->GetLargestPossibleRegion());
	for(labelItr.GoToBegin(),oItr.GoToBegin();
		!oItr.IsAtEnd()&&!labelItr.IsAtEnd();
		++labelItr,++oItr)
	{
		if(labelItr.Get()==gray)
			oItr.Set(400);
		else
			oItr.Set(-400);
	}
	amyVariable retv=amyVariable::New(VTYPE_CUBE,"LC");
	retv.Get<amyCube>()->SetObj(ret);
	this->GetStack()->Push(retv);
}