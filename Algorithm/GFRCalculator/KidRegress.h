#pragma once

class KidRegress
{
public:
	double* A;
	double* B;
	double* C;
	int     Size;
	double  X;
	double  Y;
	KidRegress(double *a,double *b,double* c,int size);
	void Calculate();
	KidRegress(void);
	~KidRegress(void);
};
