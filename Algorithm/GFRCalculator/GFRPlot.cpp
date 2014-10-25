#include"GFRPlot.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"amySeriesSet.h"
#include"amyAlgorithmRunner.h"
#include"amyAlgorithmManager.h"
#include"itkImageRegionConstIterator.h"
#include"itkImageRegionIterator.h"
#include"amyArray.h"
#include"gfrcalculator.h"
void   GFRPlot::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	amyVariable v2=this->GetStack()->Pop();
	amyVariable v3=this->GetStack()->Pop();
	FETCH(amySeriesSet,sst,v1);
	FETCH(amyCube,fa1,v2);
	FETCH(amyCube,fa2,v3);

	


	//amyCube::tCube::Pointer medobj=amyCube::tCube::New();
	//medobj->SetRegions(fa1.obj->GetLargestPossibleRegion());
	//medobj->SetSpacing(fa1.obj->GetSpacing());
	//medobj->SetDirection(fa1.obj->GetDirection());
	//medobj->Allocate();


	//typedef itk::ImageRegionIterator<amyCube::tCube> ItrType;
	//typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrConstType;
	//
	//ItrType Itr(medobj,medobj->GetLargestPossibleRegion());
	//ItrConstType CItr1(fa1.obj,fa1.obj->GetLargestPossibleRegion());
	//ItrConstType CItr2(fa2.obj,fa2.obj->GetLargestPossibleRegion());

	//for(Itr.GoToBegin(),CItr1.GoToBegin(),CItr2.GoToBegin();
	//	!Itr.IsAtEnd()&&!CItr1.IsAtEnd()&&!CItr2.IsAtEnd();
	//	++Itr,++CItr1,++CItr2)
	//{
	//	if(CItr1.Get()>0&&CItr2.Get()<0)
	//	{
	//		Itr.Set(400);
	//	}
	//	else
	//	{
	//		Itr.Set(-400);
	//	}
	//}

	//amyVariable medvar=amyVariable::New(VTYPE_CUBE,"MED");
	//FETCH(amyCube,medcube,medvar);
	//medcube.SetObj(medobj);


	amyAlgorithm* TDCal=amyAlgorithmManager::GetInstance()->GetAlgorithmByName("TDCalculator");
	amyAlgorithm* AvgTDCal=amyAlgorithmManager::GetInstance()->GetAlgorithmByName("AvgTDCalculator");
	
	
	vector<amyVariable> input1,output1;
	input1.push_back(v1);
	input1.push_back(v3);
	bool flag=amyAlgorithmRunner::GetInstance()->Start(TDCal,input1,output1);
	if(flag==0)
	{
		this->PostError("TDCError");
		return;
	}
	FETCH(amyArray,corarr,output1[0]);

	vector<amyVariable> inputavg,outputavg;
	inputavg.push_back(v1);
	inputavg.push_back(v3);
	flag=amyAlgorithmRunner::GetInstance()->Start(AvgTDCal,inputavg,outputavg);
	if(flag==0)
	{
		this->PostError("TDCError");
		return;
	}
	FETCH(amyArray,avgcorarr,outputavg[0]);
	
	
	
	vector<amyVariable> input2,output2;
	input2.push_back(v1);
	input2.push_back(v2);
	flag=amyAlgorithmRunner::GetInstance()->Start(TDCal,input2,output2);
	if(flag==0)
	{
		this->PostError("TDCError");
		return;
	}
	FETCH(amyArray,wholearr,output2[0]);
	if(corarr().size()!=wholearr().size())
	{
		this->PostError("TDCError");
		return;	
	}
	vector<float> medarr;
	for(int i=0;i<wholearr().size();i++)
	{
		medarr.push_back(wholearr()[i]*5.1788/1000.0-avgcorarr()[i]*15124*5.1788/1000.0);
	}

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"GARR");
	FETCH(amyArray,retarr,ret);
	
	this->GetStack()->Push(v1);
	TimePointArr t;
	t.Run();
	amyVariable timevar=this->GetStack()->Pop();
	FETCH(amyArray,TArr,timevar);
	float sum=0;
	for(int i=0;i<corarr().size();i++)
	{
		if(i>0)
		{
			int interval=(TArr()[i]-TArr()[i-1]);
			sum+=(avgcorarr()[i]+avgcorarr()[i-1])*(double)interval/2.0;
		}
		if(sum!=0)
		{
			retarr().push_back(medarr[i]/sum*60/0.7);
		}
		else
		{
			retarr().push_back(0);
		}
	}
	this->GetStack()->Push(ret);
}