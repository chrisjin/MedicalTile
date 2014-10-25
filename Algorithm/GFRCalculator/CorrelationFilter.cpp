//#include"CorrelationFilter.h"
//#include"amyTypeWrap.h"
//#include"amyAlgorithmStack.h"
//#include"amyscanf.h"
//float Correlation(vector<float>& a,vector<float>& b)
//{
//	int num=a.size()<b.size()?a.size():b.size();
//	float xys=0,xsys=0,x2s=0,xs2=0,y2s=0,ys2=0;
//	float xs=0,ys=0;
//	for(int i=0;i<num;i++)
//	{
//		xys+=a[i]*b[i];
//		xs+=a[i];
//		ys+=b[i];
//		x2s+=a[i]*a[i];
//		y2s+=b[i]*b[i];
//	}
//	xsys=xs*ys;
//	xs2=xs*xs;
//	ys2=ys*ys;
//	float ret=(num*xys-xsys)/(sqrt(num*x2s-xs2)*sqrt(num*y2s-ys2));
//	//float div=fabs(a[num-1]-a[0]);
//	//if(div<=0)div=0;
//	//ret=ret*div;
//	return ret;
//}
//void CorrelationFilter::Run()
//{
//	amyPointArr::Keeper kp=this->GetStack()->Pop().Get<amyPointArr>();
//	int range=1;
//	amyUtil::scanf("Radius:%d",&range);
//
//	
//	amyVariable ret=amyVariable::New(VTYPE_FLOAT_ARR,"Cor");
//	for(int i=0;i<kp->pointarr.size();i++)
//	{
//		vector<float> xa;
//		vector<float> ya;
//		for(int j=i-range;j<=i+range;j++)
//		{
//			float vx=-1000;
//			float vy=1000;
//			if(j>=0&&j<kp->pointarr.size())
//			{	
//				vx=kp->pointarr[j].x;
//				vy=kp->pointarr[j].y;
//			}
//			xa.push_back(vx);
//			ya.push_back(vy);
//		}
//		float c=Correlation(xa,ya);
//		ret.Get<amyFloatArr>()->arr.push_back(c);
//	}
//
//	this->GetStack()->Push(ret);
//	
//
//	
//}