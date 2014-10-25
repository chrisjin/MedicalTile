#include"amyVoxelCounter.h"
#include"amyAlgorithmStack.h"
#include"itkImageRegionConstIterator.h"
#include"amyVariable.h"
#include"amyCube.h"
#include"amyNumber.h"
void amyVoxelCounter::Run()
{
	amyVariable v=this->GetStack()->Pop();
	if(v.GetType()!=VTYPE_CUBE)
		return;
	amyCube::Keeper c=v.Get<amyCube>();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;
	ItrType Itr(c->obj,c->obj->GetLargestPossibleRegion());
	int count=0;
	for(Itr.GoToBegin();!Itr.IsAtEnd();++Itr)
	{
		if(Itr.Get()>0)
			count++;
	}

	amyVariable ret=amyVariable::New(VTYPE_DATA_NUMBER,"VCount");
	FETCH(amyNumber,n,ret);
	n()=count;
	this->GetStack()->Push(ret);
}

void amyVolumeCounter::Run()
{
	amyVariable v=this->GetStack()->Pop();
	if(v.GetType()!=VTYPE_CUBE)
		return;
	amyCube::Keeper c=v.Get<amyCube>();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;
	ItrType Itr(c->obj,c->obj->GetLargestPossibleRegion());
	int count=0;
	for(Itr.GoToBegin();!Itr.IsAtEnd();++Itr)
	{
		if(Itr.Get()>0)
			count++;
	}
	amyCube::tCube::SpacingType sp=c->obj->GetSpacing();

	amyVariable ret=amyVariable::New(VTYPE_DATA_NUMBER,"VCount");
	FETCH(amyNumber,n,ret);
	n()=(float)count*sp[0]*sp[1]*sp[2];
	this->GetStack()->Push(ret);
}