#include"RegionGrow.h"
#include"amyVariable.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"amyscanf.h"
#include"ThresholdWidget.h"
#include"ClosingAndOpenning.h"
#include"LargestComponent.h"
#include"FillHoleForEverySlice.h"
#include"EdgePreserveSmooth.h"
DLL_IMPL_BEGIN(9)
	//DLL_ALGO(RegionGrow,0)
	DLL_ALGO(ThresholdDIY,0)
	DLL_ALGO(Opening,1)
	DLL_ALGO(Closing,2)
	DLL_ALGO(Gaussian,3)
	DLL_ALGO(Erode,4)
	DLL_ALGO(LargestComponent,5)
	DLL_ALGO(FillHoleForEverySlice,6)
	DLL_ALGO(EdgePreserveSmooth,7)
DLL_IMPL_END
//void RegionGrow::Run()
//{ 
//	int a=3,b=4;
//	amyUtil::scanf("PingSaoNum:%d\nInterval:%d",&a,&b);
//	
//	//int a=999;
//	//char mm[50]={0};
//	//float sp[3]={1.1,1.2,1.3};
//	//float timeinterval=10;
//	//amyUtil::scanf("AAAA\nBBBB\nCCC");
//	//vector<float> arr;
//	//arr.push_back(0.1);
//	//arr.push_back(0.2);
//	//amyUtil::scanf("KKK%d,%",arr);
//	//amyUtil::scanf("aaa%dmmmm%s",&a,mm);
//	////QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//	//amyAlgorithmStack* stack=this->GetStack();
//	//amyVariable v1=stack->Pop();
//
//	//if(v1.GetType()!=VTYPE_CUBE)
//	//	return;
//
//	//amyVariable v3=amyVariable::New(VTYPE_CUBE,"Ret");
//	//amyCube* cube3=(amyCube*)v3.Get();
//	//cube3->Copy((amyCube*)v1.Get());
//	//stack->Push(v3);
//}




void ThresholdDIY::Run()
{
	amyVariable v=this->GetStack()->Pop();
	amyCube::Keeper kcube=v.Get<amyCube>();
	WDialog d;
	d.m_W->SetInput(kcube);
	d.exec();

	amyVariable ret=amyVariable::New(d.m_W->GetMask(),VTYPE_CUBE,"Ret");
	this->GetStack()->Push(ret);
}
