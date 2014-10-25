#include "KidRegress.h"

KidRegress::KidRegress(void)
{
}

KidRegress::~KidRegress(void)
{
}

KidRegress::KidRegress(double *a,double *b,double* c,int size)
{
	A=a;
	B=b;
	C=c;
	Size=size;
}
void KidRegress::Calculate()
{
	double SA2=0;
	for(int i=0;i<Size;i++)
	{
		SA2+=A[i]*A[i];
		
	}
	double SB2=0;
	for(int i=0;i<Size;i++)
	{
		SB2+=B[i]*B[i];
	}
	double SAC=0;
	for(int i=0;i<Size;i++)
	{
		SAC+=A[i]*C[i];
	}
	double SBC=0;
	for(int i=0;i<Size;i++)
	{
		SBC+=B[i]*C[i];
	}
	double SAB=0;
	for(int i=0;i<Size;i++)
	{
		SAB+=A[i]*B[i];
	}
	double SC2=0;
	for(int i=0;i<Size;i++)
	{
		SC2+=C[i]*C[i];
	}

	double c_a=SA2,c_b=SB2,c_c=-2*SAC,c_d=-2*SBC,c_e=2*SAB,c_f=SC2;


	Y=-(c_c*c_e-2*c_a*c_d)/(c_e*c_e-4*c_a*c_b);
	X=-(2*c_b*c_c-c_e*c_d)/(4*c_a*c_b-c_e*c_e);


}