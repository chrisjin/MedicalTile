#include"ROISegmentaion.h"
#include<QMessageBox>
#include"amyVariable.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"ROIDialog.h"
#include <itkImageRegionIteratorWithIndex.h>
#include <itkMaximumProjectionImageFilter.h>
#include<itkOtsuThresholdImageFilter.h>
#include"itkRegionOfInterestImageFilter.h"
#include"amyPure.h"
DLL_IMPL_BEGIN(1)
	DLL_ALGO(ROISegmentaion,0)
DLL_IMPL_END
void ROISegmentaion::Run()
{ 
	 
	//QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	amyAlgorithmStack* stack=this->GetStack();
	amyVariable v1=stack->Pop();

	if(v1.GetType()!=VTYPE_CUBE)
		return;
	typedef itk::MaximumProjectionImageFilter<amyCube::tCube,amyCube::tCube> MIPType;
	MIPType::Pointer mipfilter=MIPType::New();
	mipfilter->SetInput(v1.Get<amyCube>()->obj);
	mipfilter->Update();

	amyCube* cube=new amyCube;
	cube->SetObj(mipfilter->GetOutput());
	ROIDialog dlg;
	dlg.SetInput(cube);
	dlg.exec();
	delete cube;
	
	QRect r=dlg.GetRect();
	amyCube::Keeper c=v1.Get<amyCube>();
	amyCube::tCube::Pointer pp=c->obj;

	amyCube::tCube::RegionType region=pp->GetLargestPossibleRegion();
	amyCube::tCube::IndexType index;
	index[0]=r.left();
	index[1]=r.top();
	index[2]=0;
	amyCube::tCube::SizeType size;
	size[0]=r.width();
	size[1]=r.height();
	size[2]=region.GetSize()[2];

	amyCube::tCube::Pointer newcube=amyCube::tCube::New();
	newcube->SetRegions(region);
	newcube->SetSpacing(v1.Get<amyCube>()->obj->GetSpacing());
	newcube->Allocate();

	amyCube::tCube::RegionType rregion;
	rregion.SetIndex(index);
	rregion.SetSize(size);
	typedef itk::ImageRegionIteratorWithIndex<amyCube::tCube> ItType;
	ItType itr(pp,region);
	ItType itro(newcube,region);
	for(itro.GoToBegin(),itr.GoToBegin();!itr.IsAtEnd();++itr,++itro)
	{
		if(!rregion.IsInside(itr.GetIndex()))
			itro.Set(-400);
		else
		{
			short v=itr.Get();
			itro.Set( v);
		}

	}
	//typedef itk::RegionOfInterestImageFilter<amyCube::tCube,amyCube::tCube> ROIType;
	//ROIType::Pointer rfter=ROIType::New();
	//rfter->SetRegionOfInterest(rregion);
	//rfter->SetInput(newcube);
	////rfter->set
	newcube->SetRequestedRegion(rregion);
	//rfter->Update();
	amyVariable v3=amyVariable::New(VTYPE_CUBE,"Ret");
	amyCube::Keeper cube3=v3.Get<amyCube>();
	//cube3->SetObj(newcube);
	cube3->SetObj(newcube);
	stack->Push(v3);
}
