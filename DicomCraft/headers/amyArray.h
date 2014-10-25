#pragma once
#include"DicomMacro.h"
#include"amyKeeper.h"
#include<vector>
class DICOM_INTERFACE amyArray
{
public:
	~amyArray();
	typedef std::vector<float> tData;
	int size();
	float& at(int i);
	float& operator[](int i);
	tData& operator()();

private:
	std::vector<float> m_Data;
};

