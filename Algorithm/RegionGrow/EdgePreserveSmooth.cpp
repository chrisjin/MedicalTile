#include"EdgePreserveSmooth.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"itkCurvatureAnisotropicDiffusionImageFilter.h"
#include"itkCastImageFilter.h"
void EdgePreserveSmooth::Run()
{
	amyVariable v=this->GetStack()->Pop();
	FETCH(amyCube,cube,v);
	typedef itk::Image<float,3> FloatImageType;
	typedef itk::CastImageFilter<amyCube::tCube,FloatImageType> I2FType;
	typedef itk::CastImageFilter<FloatImageType,amyCube::tCube> F2IType;

	I2FType::Pointer I2F=I2FType::New();
	I2F->SetInput(cube.obj);
	
	typedef itk::CurvatureAnisotropicDiffusionImageFilter<FloatImageType,FloatImageType> FilterType;
	FilterType::Pointer filter=FilterType::New();
	filter->SetInput(I2F->GetOutput());
	filter->SetConductanceParameter(3.0);
	filter->SetTimeStep(0.0625);
	filter->SetNumberOfIterations(5);
	
	F2IType::Pointer F2I=F2IType::New();
	F2I->SetInput(filter->GetOutput());
	F2I->Update();

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"ret");
	FETCH(amyCube,retcube,ret);
	retcube.SetObj(F2I->GetOutput());
	this->GetStack()->Push(ret);
}