#include"ClosingAndOpenning.h"
#include"itkGrayscaleMorphologicalOpeningImageFilter.h"
#include"itkGrayscaleMorphologicalClosingImageFilter.h"
#include"amyCube.h"
#include"amyAlgorithmStack.h"
#include"itkBinaryBallStructuringElement.h"
#include"itkDiscreteGaussianImageFilter.h"
#include"itkGrayscaleErodeImageFilter.h"
#include"amyscanf.h"
string BasicFilter::GetDescription()
{
	return "Select one cube and click the button";
}


void Opening::Run()
{
	amyCube::Keeper c1=this->GetStack()->Pop().Get<amyCube>();
	typedef itk::BinaryBallStructuringElement<short,3 >  Structuring3DElementType;	
	typedef itk::GrayscaleMorphologicalOpeningImageFilter<amyCube::tCube,amyCube::tCube,Structuring3DElementType> tF;
	
	int x=1,y=1,z=1;
	amyUtil::scanf("Opening Kernel Size:\nX:%d\nY:%d\nZ:%d",&x,&y,&z);
	amyCube::tCube::SizeType size;
	size[0]=x;
	size[1]=y;
	size[2]=z;
	Structuring3DElementType kernel;
	kernel.SetRadius(size);
	kernel.CreateStructuringElement();
	
	tF::Pointer f=tF::New();
	f->SetInput(c1->obj);
	f->SetKernel(kernel);
	f->Update();


	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Opening");
	ret.Get<amyCube>()->SetObj(f->GetOutput());
	this->GetStack()->Push(ret);

}


void Closing::Run()
{
	amyCube::Keeper c1=this->GetStack()->Pop().Get<amyCube>();
	typedef itk::BinaryBallStructuringElement<short,3 >  Structuring3DElementType;	
	typedef itk::GrayscaleMorphologicalClosingImageFilter<amyCube::tCube,amyCube::tCube,Structuring3DElementType> tF;
	
	int x=2,y=2,z=2;
	amyUtil::scanf("Closing Kernel Size:\nX:%d\nY:%d\nZ:%d",&x,&y,&z);
	amyCube::tCube::SizeType size;
	size[0]=x;
	size[1]=y;
	size[2]=z;
	Structuring3DElementType kernel;
	kernel.SetRadius(size);
	kernel.CreateStructuringElement();
	
	tF::Pointer f=tF::New();
	f->SetInput(c1->obj);
	f->SetKernel(kernel);
	f->Update();


	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Closing");
	ret.Get<amyCube>()->SetObj(f->GetOutput());
	this->GetStack()->Push(ret);

}

void Gaussian::Run()
{
	amyCube::Keeper c1=this->GetStack()->Pop().Get<amyCube>();
	typedef itk::DiscreteGaussianImageFilter<amyCube::tCube,amyCube::tCube> tF;
	tF::Pointer f=tF::New();
	
	float Variance=1.5;
	amyUtil::scanf("Gaussian Variance:%f",&Variance);
	f->SetInput(c1->obj);
	f->SetVariance(Variance);
	f->Update();

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Gaussian");
	ret.Get<amyCube>()->SetObj(f->GetOutput());
	this->GetStack()->Push(ret);
}

void Erode::Run()
{
	amyCube::Keeper c1=this->GetStack()->Pop().Get<amyCube>();
	typedef itk::BinaryBallStructuringElement<short,3 >  Structuring3DElementType;	
	typedef itk::GrayscaleErodeImageFilter<amyCube::tCube,amyCube::tCube,Structuring3DElementType> tF;
	
	int x=2,y=2,z=2;
	amyUtil::scanf("Erode Kernel Size:\nX:%d\nY:%d\nZ:%d",&x,&y,&z);
	amyCube::tCube::SizeType size;
	size[0]=x;
	size[1]=y;
	size[2]=z;
	Structuring3DElementType kernel;
	kernel.SetRadius(size);
	kernel.CreateStructuringElement();
	
	tF::Pointer f=tF::New();
	f->SetInput(c1->obj);
	f->SetKernel(kernel);
	f->SetBoundary(0);
	f->Update();


	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Erode");
	ret.Get<amyCube>()->SetObj(f->GetOutput());
	this->GetStack()->Push(ret);
}