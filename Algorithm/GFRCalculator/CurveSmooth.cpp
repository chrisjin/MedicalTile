#include"CurveSmooth.h"
#include"amyTypeWrap.h"
#include"amyAlgorithmStack.h"
#include"amyscanf.h"
#include"amyArray.h"
void CurveSmooth::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	FETCH(amyArray,kfa,v1);
	int range=1;
	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"Smed");
	FETCH(amyArray,retarr,ret);
	vector<float>& retv=retarr();
	amyUtil::scanf("Radius:%d",&range);
	for(int i=0;i<kfa.size();i++)
	{
		float add=0;
		for(int j=i-range;j<=i+range;j++)
		{
			int index;
			if(j<=0)
				index=0;
			else if(j>=kfa.size())
				index=kfa.size()-1;
			else
				index=j;
			add+=kfa[index];
		}
		retv.push_back(add/(float)(2*range+1));

	}

	this->GetStack()->Push(ret);
}

void CurveDiff::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	FETCH(amyArray,kfa,v1);

	amyVariable ret=amyVariable::New(VTYPE_DATA_ARRAY,"Smed");
	FETCH(amyArray,retarr,ret);
	retarr().push_back(0);

	for(int i=1;i<kfa.size();i++)
	{
		retarr().push_back(kfa()[i]-kfa()[i-1]);
	}

	this->GetStack()->Push(ret);
}