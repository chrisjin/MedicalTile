#include"FillHoleForEverySlice.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"itkImageRegionIterator.h"
#include"itkBinaryThresholdImageFunction.h"
#include"itkFloodFilledImageFunctionConditionalIterator.h"
#include"itkImageRegionIteratorWithIndex.h"

typedef itk::Image<short,2> ImageType;
typedef itk::ImageRegionIterator<amyCube::tCube> RCubeItrType;
typedef itk::ImageRegionIterator<ImageType>       RImageItrType;
void GetSlice(amyCube::tCube::Pointer c,ImageType::Pointer image,int s,amyCube::tCube::RegionType& regiontoslice)
{
	amyCube::tCube::RegionType largestregion=c->GetLargestPossibleRegion();
	amyCube::tCube::IndexType  indextoslice=largestregion.GetIndex();
	indextoslice[2]=s;
	amyCube::tCube::SizeType   sizetoslice=largestregion.GetSize();
	sizetoslice[2]=1;
	regiontoslice.SetIndex(indextoslice);
	regiontoslice.SetSize(sizetoslice);

	RCubeItrType itrtoslice(c,regiontoslice);
	RImageItrType itrcopy(image,image->GetLargestPossibleRegion());
	for(itrtoslice.GoToBegin(),itrcopy.GoToBegin();
		!itrtoslice.IsAtEnd()&&!itrcopy.IsAtEnd();
		++itrtoslice,++itrcopy)
	{
		itrcopy.Set(itrtoslice.Get());
	}
}


void FillHoleForEverySlice::Run()
{
	amyCube::Keeper cube=this->GetStack()->Pop().Get<amyCube>();
	amyCube::tCube::RegionType largestregion=cube->obj->GetLargestPossibleRegion();

	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
	retcube->SetRegions(cube->obj->GetLargestPossibleRegion());
	retcube->SetSpacing(cube->obj->GetSpacing());
	retcube->Allocate();
	retcube->FillBuffer(0);
	/////¿ÕÍ¼Ïñ
	ImageType::Pointer ImageToGrow=ImageType::New();
	ImageType::SizeType imsize;
	imsize[0]=largestregion.GetSize()[0];
	imsize[1]=largestregion.GetSize()[1];
	ImageType::IndexType imindex;
	imindex[0]=largestregion.GetIndex()[0];
	imindex[1]=largestregion.GetIndex()[1];
	ImageType::RegionType imregion;
	imregion.SetSize(imsize);
	imregion.SetIndex(imindex);
	ImageToGrow->SetRegions(imregion);
	ImageToGrow->Allocate();

	//////È¡²ã
	int z=largestregion.GetSize()[2];
	for(int i=0;i<z;i++)
	{
		amyCube::tCube::RegionType regiontoslice;
		GetSlice(cube->obj,ImageToGrow,i,regiontoslice);
		
		ImageType::IndexType index;
		index[0]=0;
		index[1]=0;
		typedef itk::BinaryThresholdImageFunction<ImageType, double > FunctionType;
		FunctionType::Pointer function = FunctionType::New();
		function->SetInputImage(ImageToGrow);
		ImageType::PixelType pv=ImageToGrow->GetPixel(index);
		function->ThresholdBetween (pv-10,pv+10); // we are looking to capture 255
		typedef itk::FloodFilledImageFunctionConditionalIterator<ImageType, FunctionType > IteratorType;

		itk::Index<2> seed;
		seed[0] =0;
		seed[1] =0;
		//seed[2]=  m_MainWidget->m_MaskLing->GetSlice();
		std::vector<itk::Index<2> > seeds;
		seeds.push_back(seed);

		IteratorType it (ImageToGrow, function, seeds);
		it.GoToBegin();

		while ( !it.IsAtEnd() )
		{
			ImageType::IndexType index=it.GetIndex();
			amyCube::tCube::IndexType cubeindex;
			cubeindex[0]=index[0];
			cubeindex[1]=index[1];
			cubeindex[2]=i;
			retcube->SetPixel(cubeindex,10000);
			++it;
		}

		RCubeItrType itr(retcube,regiontoslice);
		for(itr.GoToBegin();!itr.IsAtEnd();++itr)
		{
			if(itr.Get()==10000)
			{
				itr.Set(-400);
			}
			else
			{
				itr.Set(400);
			}
		}
	}//for
	amyVariable ret=amyVariable::New(VTYPE_CUBE,"HFed");
	ret.Get<amyCube>()->SetObj(retcube);
	this->GetStack()->Push(ret);

}