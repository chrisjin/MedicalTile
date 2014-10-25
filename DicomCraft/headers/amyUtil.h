#pragma once
#include"DicomMacro.h"
#include<Windows.h>
#include"amyKeeper.h"
#include"amyPure.h"
class QImage;
class amySeries;
class amyCube;
class amyPatient;
class amySeriesSet;
namespace amyUtil
{
void    DICOM_INTERFACE GetWindowCenterWidth(amyCube* cube,int& c,int &w);
void    DICOM_INTERFACE GetCubeMinMax(amyCube* cube,int& min,int& max);
void    DICOM_INTERFACE GetCubeMinMax(amyCube* cube,int slice,int& min,int& max);
enum ePlane
{
	AXIAL,
	SAGITTAL,
	CORONAL,
	UNKNOWN
};
ePlane  DICOM_INTERFACE GetPlaneType(amyCube* cube);

amyKeeper<amyPatient> DICOM_INTERFACE MakePatientFromSeriesSet(amyKeeper<amySeriesSet> ser);
class DICOM_INTERFACE Lock
{
	DEFINE_SINGLETON(Lock)
public:
	Lock();
	void EnterCritical();
	void LeaveCritical();
private:
	CRITICAL_SECTION m_Cs;
};
}
