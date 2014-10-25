#pragma once
#include"DicomMacro.h"
#include<vector>
#include"amyWin32.h"
#include<map>
#include<string>
#include"amyKeeper.h"
using namespace std;
class amySlice;
class amySeries;
class DICOM_INTERFACE amySeriesSplitter
{
public:
	amySeriesSplitter();
	void Reset();
	void AddSlice(amyKeeper<amySlice> slice);
	void Sort();
	amySeries* NextSeries();
private:
	vector<amyKeeper<amySlice>> m_SliceArr;
	unsigned int  CurrentPos;
	unsigned int  CurrentPosInSubSer;
	float Thickness;
	float SpaceBtw;
	amySeries* CurrentSubseries;
};


//
//class amyPatient;
//class amyPatientSplitter
//{
//public:
//	void Reset();
//	void AddSlice(amySlice* slice);
//	void Sort();
//	amyPatient* NextPatient();
//private:
//	vector<amySlice*> m_SliceArr;
//
//};

class amyPatient; 
class amySeriesSet;
class DICOM_INTERFACE amyDCMFolder:public amyFolder
{
public:
	NEW_MACRO(amyDCMFolder)
	virtual void OnFindFile(const char* name);
	void Parse();
	vector<amyKeeper<amyPatient>>& GetPatientArr(){return m_PatientArr;}
	void InsertSeriesSet(amyKeeper<amySeriesSet> sst);
private:
	map<string,amySeriesSplitter*> m_Name2Splitter;
	vector<amySeriesSplitter*> m_SplitterArr;
	vector<amyKeeper<amyPatient>> m_PatientArr;
};