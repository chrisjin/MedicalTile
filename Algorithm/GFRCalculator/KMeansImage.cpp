#include"KMeansImage.h"
#include"amyAlgorithmStack.h"
#include"amySeriesSet.h"
#include"amyCube.h"
#include"itkImageRegionConstIterator.h"
#include"amySeriesManager.h"
#include"itkImageRegionIterator.h"
#include"itkImageRegionConstIteratorWithIndex.h"
class Pixel2TDC
{
public:
	int x;
	int y;
	int z;
	int size;
	float TDC[0];
};
typedef float* TDCType;
#define ALLOC_TDC(num) ((Pixel2TDC*)malloc(sizeof(Pixel2TDC)+num*sizeof(float)))
#define RELEASE_TDC(p) free(p)
#define COPY_TDC(tdcdes,tdcsrc,num) memcpy(tdcdes,tdcsrc,sizeof(Pixel2TDC)+num*sizeof(float))
void SmoothTDC(TDCType t1,int size)
{
	vector<float> arr;
	for(int i=0;i<size;i++)
	{
		float sum=0;
		for(int j=-1;j<=1;j++)
		{
			if(i+j>=0&&i+j<size)
				sum+=t1[i+j];
			else
				sum+=0;
		}
		sum=sum/3.0;
		arr.push_back(sum);
	}
	for(int i=0;i<size;i++)
	{
		t1[i]=arr[i];
	}
}
float CalDis(TDCType t1,TDCType t2,int size)
{
	//float sum=0;
	//for(int i=0;i<size;i++)
	//{
	//	sum+=(t1[i]-t2[i])*(t1[i]-t2[i]);
	//}
	//return sqrt(sum);

	float d1=0,d2=0;
	for(int i=0;i<size;i++)
	{
		d1+=t1[i]*t1[i];
	}
	d1=sqrt(d1);

	for(int i=0;i<size;i++)
	{
		d2+=t2[i]*t2[i];
	}
	d2=sqrt(d2);

	float xmul=0;
	for(int i=0;i<size;i++)
	{
		xmul+=t1[i]*t2[i];
	}

	float cosa=xmul/(d1*d2);

	return 1-cosa;
}
void CalCentralPos(vector<Pixel2TDC*>& tdcarr,TDCType cpos,int size)
{
	for(int i=0;i<size;i++)
	{
		cpos[i]=0;
	}
	for(int i=0;i<tdcarr.size();i++)
	{
		for(int j=0;j<tdcarr[i]->size;j++)
		{
			cpos[j]+=tdcarr[i]->TDC[j];
		}
	}
	for(int i=0;i<size;i++)
	{
		cpos[i]/=float(tdcarr.size());
	}
}

void   KMeansImage::Run()
{
	int test=sizeof(Pixel2TDC);
	
	amyVariable v1=this->GetStack()->Pop();
	FETCH(amySeriesSet,set,v1);
	amyVariable v2=this->GetStack()->Pop();
	FETCH(amyCube,mask,v2);

	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);

	//amyCube::tCube::Pointer retcube=amyCube::tCube::New();
	//retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
	//retcube->SetSpacing(cubeobj->obj->GetSpacing());
	//retcube->Allocate();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	typedef itk::ImageRegionConstIteratorWithIndex<amyCube::tCube> CItrTypeWI;
	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
	vector<CItrType> ItrArr;
	vector<amyCube::Keeper> PreventFromReleasing;
	vector<amyCube::tCube::Pointer> Fuck;
	for(int i=0;i<set.seriesarr.size();i++)
	{
		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
		PreventFromReleasing.push_back(kcube);
		ItrArr.push_back(CItrType(kcube->obj,kcube->obj->GetLargestPossibleRegion()));
	}

	CItrTypeWI Itrmask(mask.obj,mask.obj->GetLargestPossibleRegion());
	vector<Pixel2TDC*> Total;
	int TDCsize=ItrArr.size();
	while(1)
	{
		if(Itrmask.IsAtEnd())
			break;
		if(Itrmask.Get()>0)
		{
			Pixel2TDC* ptdc=ALLOC_TDC(ItrArr.size());
			ptdc->x=Itrmask.GetIndex()[0];
			ptdc->y=Itrmask.GetIndex()[1];
			ptdc->z=Itrmask.GetIndex()[2];
			ptdc->size=ItrArr.size();
			for(int i=0;i<ItrArr.size();i++)
			{
				ptdc->TDC[i]=ItrArr[i].Get();
			}
			//SmoothTDC(ptdc->TDC,ItrArr.size());
			Total.push_back(ptdc);
		}
		for(int i=0;i<ItrArr.size();i++)
		{
			++ItrArr[i];
		}
		++Itrmask;
	}
	
	vector<Pixel2TDC*> C1;
	vector<Pixel2TDC*> C2;
	vector<Pixel2TDC*> C3;
	C1.push_back(Total[0]);
	C2.push_back(Total[Total.size()/2]);
	C3.push_back(Total[Total.size()-1]);
	TDCType CP1=(TDCType)malloc(TDCsize*sizeof(float)) ;;
	TDCType CP2=(TDCType)malloc(TDCsize*sizeof(float)) ;
	TDCType CP3=(TDCType)malloc(TDCsize*sizeof(float)); 
	TDCType newCP1=(TDCType)malloc(TDCsize*sizeof(float)); 
	TDCType newCP2=(TDCType)malloc(TDCsize*sizeof(float)) ;
	TDCType newCP3=(TDCType)malloc(TDCsize*sizeof(float)) ;

	CalCentralPos(C1,CP1,TDCsize);
	CalCentralPos(C2,CP2,TDCsize);
	CalCentralPos(C3,CP3,TDCsize);
	while(1)
	{
		C1.clear();
		C2.clear();
		C3.clear();

		for(int i=0;i<Total.size();i++)
		{
			float d1=CalDis(Total[i]->TDC,CP1,TDCsize);
			float d2=CalDis(Total[i]->TDC,CP2,TDCsize);
			float d3=CalDis(Total[i]->TDC,CP3,TDCsize);
			if(d1<=d2/*&&d1<=d3*/)
				C1.push_back(Total[i]);
			else if(d2<=d1/*&&d2<=d3*/)
				C2.push_back(Total[i]);
			else 
				C3.push_back(Total[i]);
		}

		CalCentralPos(C1,newCP1,TDCsize);
		CalCentralPos(C2,newCP2,TDCsize);
		CalCentralPos(C3,newCP3,TDCsize);

		float diff1=CalDis(CP1,newCP1,TDCsize);
		float diff2=CalDis(CP2,newCP2,TDCsize);
		float diff3=CalDis(CP3,newCP3,TDCsize);

		if(diff1<=0.01&&diff2<=0.01/*&&diff3<=0.01*/)
		{
			break;
		}
		else
		{
			memcpy(CP1,newCP1,sizeof(float)*TDCsize);
			memcpy(CP2,newCP2,sizeof(float)*TDCsize);
			memcpy(CP3,newCP3,sizeof(float)*TDCsize);
		}
	}

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"ret");
	FETCH(amyCube,retcube,ret);
	amyCube::tCube::Pointer retobj=amyCube::tCube::New();
	retobj->SetRegions(mask.obj->GetLargestPossibleRegion());
	retobj->SetDirection(mask.obj->GetDirection());
	retobj->SetSpacing(mask.obj->GetSpacing());
	retobj->Allocate();
	retobj->FillBuffer(-200);
	for(int i=0;i<C1.size();i++)
	{
		amyCube::tCube::IndexType index;
		index[0]=C1[i]->x;
		index[1]=C1[i]->y;
		index[2]=C1[i]->z;
		retobj->SetPixel(index,0);
	}
	for(int i=0;i<C2.size();i++)
	{
		amyCube::tCube::IndexType index;
		index[0]=C2[i]->x;
		index[1]=C2[i]->y;
		index[2]=C2[i]->z;
		retobj->SetPixel(index,200);
	}
	for(int i=0;i<C3.size();i++)
	{
		amyCube::tCube::IndexType index;
		index[0]=C3[i]->x;
		index[1]=C3[i]->y;
		index[2]=C3[i]->z;
		retobj->SetPixel(index,400);
	}
	retcube.SetObj(retobj);

	this->GetStack()->Push(ret);
}