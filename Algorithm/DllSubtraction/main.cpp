#include"amyAlgorithm.h"
//#include"amySubtractionAlgorithm.h"
#include"amyAlgorithmStack.h"
#include"itkImage.h"
#include"itkSubtractImageFilter.h"
#include"amyCube.h"
#include"main.h"
DLL_IMPL_BEGIN(1)
	DLL_ALGO(amyDLLSubtractionAlgorithm,0)
DLL_IMPL_END
void amyDLLSubtractionAlgorithm::Run()
{
	amyAlgorithmStack* stack=this->GetStack();
	amyVariable v1=stack->Pop();
	amyVariable v2=stack->Pop();
	if(v1.GetType()!=VTYPE_CUBE||v2.GetType()!=VTYPE_CUBE)
		return;
	amyCube::Keeper cube1=v1.Get<amyCube>();
	amyCube::Keeper cube2=v2.Get<amyCube>();
	amyCube::tCube::RegionType region1=cube1->obj->GetLargestPossibleRegion();
	amyCube::tCube::RegionType region2=cube2->obj->GetLargestPossibleRegion();
	if(region1!=region2)
		return;
	amyCube::tCube::Pointer pretcube=amyCube::tCube::New();
	pretcube->SetSpacing(cube1->obj->GetSpacing());
	pretcube->SetRegions(region1);
	pretcube->Allocate();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
	CItrType Itr1(cube1->obj,region1);
	CItrType Itr2(cube2->obj,region2);
	ItrType  RetItr(pretcube,region1);
	for(Itr1.GoToBegin(),Itr2.GoToBegin(),RetItr.GoToBegin();
		!Itr1.IsAtEnd()&&!Itr2.IsAtEnd()&&!RetItr.IsAtEnd();
		++Itr1,++Itr2,++RetItr)
	{
		RetItr.Set(Itr1.Get()-Itr2.Get());
	}
	//typedef itk::SubtractImageFilter<amyCube::tCube> SubtractType;
	//SubtractType::Pointer subtract=SubtractType::New();
	//subtract->SetInput1(cube1->obj);
	//subtract->SetInput2(cube2->obj);
	//subtract->Update();
	amyVariable v3=amyVariable::New(VTYPE_CUBE,"Ret");
	amyCube::Keeper cube3=v3.Get<amyCube>();
	cube3->SetObj(pretcube);
	stack->Push(v3);
}
