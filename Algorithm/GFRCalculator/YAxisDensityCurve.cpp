#include"YAxisDensityCurve.h"
#include"amyVariable.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"itkImageRegionConstIterator.h"
#include"amyArray.h"
void   YAxisDensityCurve::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();
	FETCH(amyCube,cube,v1);
	FETCH(amyCube,mask,v2);
	amyCube::tCube::RegionType region=cube.obj->GetLargestPossibleRegion();
	amyCube::tCube::SizeType    size=region.GetSize();
	int yrange=size[1];
	size[1]=1;
	amyCube::tCube::IndexType   index=region.GetIndex();
	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"arr");
	FETCH(amyArray,retarr,ret);
	for(int i=0;i<yrange;i++)
	{
		index[1]=i;
		region.SetIndex(index);
		region.SetSize(size);
		ItrType Itrcube(cube.obj,region);
		ItrType Itrmask(mask.obj,region);
		float add=0;
		float pixelnum=0;
		for(Itrcube.GoToBegin(),Itrmask.GoToBegin();
			!Itrcube.IsAtEnd()&&!Itrmask.IsAtEnd();
			++Itrcube,++Itrmask)
		{
			if(Itrmask.Get()>0)
			{
				add+=Itrcube.Get();
				pixelnum++;
			}
		}
		if(pixelnum!=0)
			retarr().push_back(add/pixelnum);
		else
		{
			retarr().push_back(0);
		}
	}
	this->GetStack()->Push(ret);
}