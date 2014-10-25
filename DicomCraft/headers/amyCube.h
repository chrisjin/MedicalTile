#pragma once
#include"DicomMacro.h"
#include<vector>

#include <itkImage.h>
#include"amyKeeper.h"
using namespace std;
class DicomImage;
class amyDICOMSubseriesInfo;
class amySeries;
class DICOM_INTERFACE amyCube
{
public:	
	NEW_MACRO(amyCube)
	typedef itk::Image<short,3> tCube;
	tCube::Pointer obj;
	amyKeeper<amySeries>     series;
	int windowcenter;
	int windowwidth;
	void Copy(amyCube* cube);
	bool Open(amyKeeper<amySeries> ser);
	bool Open(vector<string>& filearr);
	void SetObj(tCube::Pointer data);
	amyCube(){}
	~amyCube();
	//vector<DicomImage*> m_ImageArr;
	//bool Open(const char* filename);
	//bool Open(amyDICOMSubseriesInfo* Subseries);
private:
	
};



class DICOM_INTERFACE amyMask
{
public:
	NEW_MACRO(amyMask)
	amyKeeper<amyCube> cube;
	amyKeeper<amyCube> mask;
	void SetMask(amyCube::tCube::Pointer ob)
	{
		mask->SetObj(ob);
	}
	amyMask()
	{
		//mask=new amyCube;
		//cube=0;
	}
};

