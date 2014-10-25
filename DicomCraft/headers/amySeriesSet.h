#pragma once
#include"DicomMacro.h"
#include"amyPure.h"
#include"amyKeeper.h"
#include<vector>
using namespace std;
class amySeries;
class amyCube;
class DICOM_INTERFACE amySeriesSet
{
public:
	NEW_MACRO(amySeriesSet)
	vector<amyKeeper<amySeries>> seriesarr;
	vector<amyKeeper<amyCube>>   cubearr;
};