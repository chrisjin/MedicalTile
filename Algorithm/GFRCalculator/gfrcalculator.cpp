#include"gfrcalculator.h"
#include"amyAlgorithmStack.h"
#include"amyTypes.h"
#include"amySeriesManager.h"
#include"amyAlgorithmBridge.h"
#include"amyscanf.h"
#include"KidRegress.h"
#include"amyDICOM.h"
#include"amyPure.h"
#include"CurveSmooth.h"
#include"amyCanvas.h"
#include<QVBoxLayout>
#include"amyChartLing.h"
#include"MultiCurveWidget.h"
#include"CorrelationFilter.h"
#include"amySeriesSet.h"
#include"amyData.h"
#include"amyNumber.h"
#include"amyMatrix.h"
#include"amyCube.h"
#include"YAxisDensityCurve.h"
#include"PeakImage.h"
#include"GFRPlot.h"
#include"VarPlot.h"
#include"MaskHistogram.h"
#include"CurveSmooth.h"
#include"DiffImage.h"
#include"KMeansImage.h"
DLL_IMPL_BEGIN(17)
	DLL_ALGO(GFRCalculator,0)
	DLL_ALGO(RegGFRCalculator,1)
	DLL_ALGO(TimePointArr,2)
	DLL_ALGO(DrawSpecial,3)
	DLL_ALGO(CurveSmooth,4)
	DLL_ALGO(CurveDiff,5)
	DLL_ALGO(YAxisDensityCurve,6)
	DLL_ALGO(PeakImage,7)
	DLL_ALGO(HalfPeakImage,8)
	DLL_ALGO(DiffImage,9)
	DLL_ALGO(SumImage,10)
	DLL_ALGO(PeakMulTimeImage,11)
	DLL_ALGO(KMeansImage,12)
	DLL_ALGO(GFRPlot,13)
	DLL_ALGO(VarPlot,14)
	DLL_ALGO(MaskHistogram,15)
	DLL_ALGO(OtsuMultiSeg,16)
DLL_IMPL_END

void GFRCalculator::Run()
{
	int num=this->GetStack()->GetSize();
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();
	amyVariable v3=this->GetStack()->Pop();

	this->GetStack()->Push(v1);
	TimePointArr t;
	t.Run();
	amyVariable v4=this->GetStack()->Pop();
	if(num==4)
		v4=this->GetStack()->Pop();
	if(v1.GetType()!=VTYPE_SERIES_SET)
		return;
	if(v2.GetType()!=VTYPE_DATA_ARRAY)
		return;
	if(v3.GetType()!=VTYPE_DATA_ARRAY)
		return;
	FETCH(amySeriesSet,sst,v1);
	FETCH(amyArray,fa1,v2);
	FETCH(amyArray,fa2,v3);
	FETCH(amyArray,TArr,v4);
	//if(num==4)
	//	TArr=v4.Get<amyFloatArr>();
	if(fa1.size()!=fa2.size())
		return;

	int PhaseNum=fa1.size();

	vector<float>& TDCAng=fa1();
	vector<float>& arr=fa2();
	vector<float>  TDCAngAcc;
	float normal1=TDCAng[0];
	float normal2=arr[0];
	for(int i=0;i<TDCAng.size();i++)
	{
		TDCAng[i]=TDCAng[i]-normal1;
		arr[i]=arr[i]-normal2;
	}
	double sum=0;
	for(int i=0;i<PhaseNum;i++)
	{
		int interval=3;
		if(i>=1)
		{
			//if(num==4)
			interval=(TArr[i]-TArr[i-1]);
			sum+=(TDCAng[i]+TDCAng[i-1])*(double)interval/2.0;
			//sum+=TDCAng[i]*interval;
			TDCAngAcc.push_back(sum);
		}
		else
		{
			TDCAngAcc.push_back(0);
		}
	}
	int T1,T2;
	int testangv=0;
	for(int i=0;i<PhaseNum;i++)
	{
		if(TDCAng[i]>testangv)
		{
			testangv=TDCAng[i];
			T1=i;
		}
	}
	T2=T1+3;
	T1=6;
	T2=15;
	float timeinterval=3.0;
	amyCube::Keeper keepercube=pSeriesManager->GetCube(sst.seriesarr[0]);
	amyCube::tCube::SpacingType sp=keepercube->obj->GetSpacing();
	float spa[3]={sp[0],sp[1],sp[2]};
	float HCT=0.325;
	
	amyUtil::scanf("PixelSize:%f,%f,%f\nTimeInterval:%f\nT1:%d;T2:%d\nHCT:%f",spa,spa+1,spa+2,&timeinterval,&T1,&T2,&HCT);
	float   volume=spa[0]*spa[1]*spa[2];
	if(T2>=TDCAng.size())
		T2=TDCAng.size()-1;
	/*int   Second1=T1*,Second2;*/
	////A1*v+B1*G=C1
	////A2*v+B2*G=C2
	double A1=TDCAng[T1];
	double B1=TDCAngAcc[T1];
	double C1=arr[T1]*volume;
	double A2=TDCAng[T2];
	double B2=TDCAngAcc[T2];
	double C2=arr[T2]*volume;

	double X1=double(C1*B2-C2*B1)/double(A1*B2-A2*B1);
	double X2=double(C1*A2-A1*C2)/double(B1*A2-B2*A1);

	//float HCT=0.325;



	amyVariable ret=amyVariable::New(VTYPE_DATA_NUMBER,"GFR");
	FETCH(amyNumber,n,ret);
	n()=X2*(1-HCT)/1000*60;
	//ret.Get<amyFloat>()->value=reg.Y*(1-HCT)/1000*60;
	this->GetStack()->Push(ret);


	amyVariable retan=amyVariable::New(VTYPE_DATA_NUMBER,"Vol");
	FETCH(amyNumber,nvol,retan);
	nvol()=X1;
	this->GetStack()->Push(retan);

}

void RegGFRCalculator::Run()
{
		int num=this->GetStack()->GetSize();
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();
	amyVariable v3=this->GetStack()->Pop();

	this->GetStack()->Push(v1);
	TimePointArr t;
	t.Run();
	amyVariable v4=this->GetStack()->Pop();
	if(num==4)
		v4=this->GetStack()->Pop();
	if(v1.GetType()!=VTYPE_SERIES_SET)
		return;
	if(v2.GetType()!=VTYPE_DATA_ARRAY)
		return;
	if(v3.GetType()!=VTYPE_DATA_ARRAY)
		return;
	FETCH(amySeriesSet,sst,v1);
	FETCH(amyArray,fa1,v2);
	FETCH(amyArray,fa2,v3);
	FETCH(amyArray,TArr,v4);
	//if(num==4)
	//	TArr=v4.Get<amyFloatArr>();
	if(fa1.size()!=fa2.size())
		return;

	int PhaseNum=fa1.size();

	vector<float>& TDCAng=fa1();
	vector<float>& arr=fa2();
	vector<float>  TDCAngAcc;
	float normal1=TDCAng[0];
	float normal2=arr[0];
	for(int i=0;i<TDCAng.size();i++)
	{
		TDCAng[i]=TDCAng[i]-normal1;
		arr[i]=arr[i]-normal2;
	}
	double sum=0;
	for(int i=0;i<PhaseNum;i++)
	{
		int interval=3;
		if(i>=1)
		{
			//if(num==4)
			interval=(TArr[i]-TArr[i-1]);
			sum+=(TDCAng[i]+TDCAng[i-1])*(double)interval/2.0;
			//sum+=TDCAng[i]*interval;
			TDCAngAcc.push_back(sum);
		}
		else
		{
			TDCAngAcc.push_back(0);
		}
	}
	int T1,T2;
	int testangv=0;
	for(int i=0;i<PhaseNum;i++)
	{
		if(TDCAng[i]>testangv)
		{
			testangv=TDCAng[i];
			T1=i;
		}
	}
	T2=T1+3;
	T1=6;
	T2=15;
	float timeinterval=3.0;
	amyCube::Keeper keepercube=pSeriesManager->GetCube(sst.seriesarr[0]);
	amyCube::tCube::SpacingType sp=keepercube->obj->GetSpacing();
	float spa[3]={sp[0],sp[1],sp[2]};
	float HCT=0.325;
	
	amyUtil::scanf("PixelSize:%f,%f,%f\nTimeInterval:%f\nT1:%d;T2:%d\nHCT:%f",spa,spa+1,spa+2,&timeinterval,&T1,&T2,&HCT);
	float   volume=spa[0]*spa[1]*spa[2];
	if(T2>=TDCAng.size())
		T2=TDCAng.size()-1;
	/*int   Second1=T1*,Second2;*/
	////A1*v+B1*G=C1
	////A2*v+B2*G=C2
	double A1=TDCAng[T1];
	double B1=TDCAngAcc[T1];
	double C1=arr[T1]*volume;
	double A2=TDCAng[T2];
	double B2=TDCAngAcc[T2];
	double C2=arr[T2]*volume;
	double* Aarr=new double[T2-T1+1];
	double* Barr=new double[T2-T1+1];
	double* Carr=new double[T2-T1+1];
	for(int i=0;i<T2-T1+1;i++)
	{
		Aarr[i]=TDCAng[i+T1];
		Barr[i]=TDCAngAcc[i+T1];
		Carr[i]=arr[i+T1]*volume;
	}
	KidRegress reg(Aarr,Barr,Carr,T2-T1+1);
	reg.Calculate();


	amyVariable ret=amyVariable::New(VTYPE_DATA_NUMBER,"GFR");
	FETCH(amyNumber,n,ret);
	n()=reg.Y*(1-HCT)/1000*60;
	this->GetStack()->Push(ret);


	delete[] Aarr;
	delete[] Barr;
	delete[] Carr;

}

int GetDifSecond(amyTime& t1,amyTime& t2)
{
	int difh=t1.hour-t2.hour;
	int difm=t1.minute-t2.minute;
	int difs=t1.second-t2.second;
	return difh*3600+difm*60+difs;
}
void TimePointArr::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	if(!v1.IsValid())
		return;
	FETCH(amySeriesSet,sst,v1);
	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"Ret");
	FETCH(amyArray,kdata,ret);
	float currenttime=0;
	amyTime currenttimestruct;
	int Pingsao=1;
	float interval=3;
	amyUtil::scanf("PingSaoNum:%d\nInterval:%f",&Pingsao,&interval);
	for(int i=0;i<sst.seriesarr.size();i++)
	{
		amySeries::Keeper kser=sst.seriesarr[i];
		amySeriesInfo* debug=sst.seriesarr[i]->info.GetPointer();
		if(i>=Pingsao+1)
		{
			amySeries::Keeper lastser=sst.seriesarr[i-1];
			if(i==Pingsao+1)
			{
				currenttimestruct=lastser->info->acquisitiontime;
			}
			
			amyTime debug1=lastser->info->acquisitiontime;
			amyTime debug2=kser->info->acquisitiontime;
			if(lastser->info->acquisitiontime==kser->info->acquisitiontime)
			{
				currenttimestruct+=interval;
				currenttime+=interval;
			}
			else
			{
				currenttime+=GetDifSecond(kser->info->acquisitiontime,currenttimestruct);
				currenttimestruct=kser->info->acquisitiontime;
			}
		}
		kdata().push_back(currenttime);
	}
	amyUtil::scanf("Time:",kdata());
	this->GetStack()->Push(ret);
}



void DrawSpecial::Run()
{
	amyVariable sst=this->GetStack()->Pop();
	this->GetStack()->Push(sst);
	TimePointArr tr;
	tr.Run();
	//amyArray
	//amyArray& kf3=this->GetStack()->Pop()(&ccc);
	//amyArray* test=vtime.Get<amyArray>().GetPointer();
	//FETCH(amyArray,kf3,vtime);//////T
	///////!!!!!必须暂存 否则Time执行完了直接Pop会全局没有array的keeper
	amyVariable vtime=this->GetStack()->Pop();
	FETCH(amyArray,kf3,vtime);
	FETCH(amyArray,kf1,this->GetStack()->Pop());
	FETCH(amyArray,kf2,this->GetStack()->Pop());
	
	vector<float>& a=kf1();
	vector<float>& time=kf3();
	vector<float>& K=kf2();
	vector<float> acc;
	int sum=0;
	for(int i=0;i<kf2.size();i++)
	{
		if(i!=0)
			sum=sum+(a[i]+a[i-1])*(time[i]-time[i-1])/2;
		else
			sum=0;
		acc.push_back(sum);
	}
	amyVariable ret=amyVariable::New(VTYPE_DATA_MATRIX,"Spe");
	FETCH(amyMatrix,kparr,ret);
	kparr.addrow(2);

	for(int i=0;i<kf2.size();i++)
	{
		float div=0;
		if(a[i]==0)
			div=0.1;
		else
			div=a[i];
		float y=K[i]/div;
		float x=acc[i]/div;
		kparr[0]().push_back(x);
		kparr[1]().push_back(y);
	}
	this->GetStack()->Push(ret);

}

