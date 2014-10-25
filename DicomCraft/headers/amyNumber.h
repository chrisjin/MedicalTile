#pragma once
#include"DicomMacro.h"
class  DICOM_INTERFACE amyNumber
{
public:
	amyNumber();
	amyNumber(float v);
	//For Retrieve
	float& operator()();
	//
	float operator=(float v);
private:
	float m_Value;
};