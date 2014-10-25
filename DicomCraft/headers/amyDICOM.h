#pragma once
#include"DicomMacro.h"
#include<string>
#include<vector>
#include"amyKeeper.h"
#include"amyPure.h"

using namespace std;
class amySeries;
/////!!!!!!!!!!!!!!!以后改为智能指针
class DICOM_INTERFACE amyPatientInfo
{
public:
	NEW_MACRO(amyPatientInfo)
	string name;
	string gender;
	uint   age;
	~amyPatientInfo()
	{
	}
};
class DICOM_INTERFACE amyPatient
{
public:
	NEW_MACRO(amyPatient)
	amyPatient(){info=new amyPatientInfo;}
	~amyPatient();
	vector<amyKeeper<amySeries>> seriesarr;
	amyKeeper<amyPatientInfo> info;
};
class amySlice;
class DICOM_INTERFACE amySeriesInfo
{
public:
	enum ePlane
	{
		AXIAL,
		SAGITTAL,
		CORONAL,
		UNKNOWN
	};
	amyDate date;
	amyTime seriestime;
	amyTime acquisitiontime;
	ePlane plane;
	~amySeriesInfo()
	{
	}
};
class DICOM_INTERFACE amySeries
{
public:
	NEW_MACRO(amySeries)
	amySeries(){info=new amySeriesInfo;patientinfo=new amyPatientInfo;}
	~amySeries();
	vector<amyKeeper<amySlice>> slicearr;
	amyKeeper<amySeriesInfo>    info;
	amyKeeper<amyPatientInfo>   patientinfo;
};
class DICOM_INTERFACE amySliceInfo
{
public:
	string filepath;
	uint imagenumber;
	float slicelocation;
	float slicethickness;
	string seriesuid;
	string seriestime;
	int windowcenter;
	int windowwidth;
	float imagepositionx;
	float imagepositiony;
	float imagepositionz;
	~amySliceInfo()
	{
	}
};
class DICOM_INTERFACE amySlice
{
public:
	NEW_MACRO(amySlice)
	~amySlice();
	amySlice(){info=new amySliceInfo;seriesinfo=new amySeriesInfo;}
	amyKeeper<amySliceInfo>  info;
	amyKeeper<amySeriesInfo> seriesinfo;
};








