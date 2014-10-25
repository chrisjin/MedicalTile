#include"amyCubeAND.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"itkImageRegionIterator.h"
void   amyCubeAND::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();
	FETCH(amyCube,cube1,v1);
	FETCH(amyCube,cube2,v2);

	amyCube::tCube::Pointer cu=amyCube::tCube::New();
	cu->SetSpacing(cube1.obj->GetSpacing());
	cu->SetRegions(cube1.obj->GetLargestPossibleRegion());
	cu->Allocate();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;

	CItrType I1(cube1.obj,cube1.obj->GetLargestPossibleRegion());
	CItrType I2(cube2.obj,cube2.obj->GetLargestPossibleRegion());
	ItrType  Ir(cu,cu->GetLargestPossibleRegion());

	for(I1.GoToBegin(),I2.GoToBegin(),I2.GoToBegin();
		!I1.IsAtEnd()&&!I2.IsAtEnd()&&!Ir.IsAtEnd();
		++I1,++I2,++Ir)
	{
		if(I1.Get()>0&&I2.Get()>0)
		{
			Ir.Set(400);
		}
		else
			Ir.Set(-400);
	}

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"ret");
	FETCH(amyCube,retcube,ret);
	retcube.SetObj(cu);
	this->GetStack()->Push(ret);
}