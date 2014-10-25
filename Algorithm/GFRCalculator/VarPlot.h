#include"PeakImage.h"


class VarPlot:public PeakImage
{
public:
	virtual const char* GetAlgorithmName(){return "VarPlot";}
	virtual void   Run();
};