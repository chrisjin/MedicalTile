#pragma once
#include"DicomMacro.h"
#include<vector>
#include"amyArray.h"
#include"amyKeeper.h"
using namespace std;

class DICOM_INTERFACE amyMatrix
{
public:
	~amyMatrix();
	amyArray& addrow();
	void addrow(int num);
	amyArray& operator[](int index);
	int rowcount();
	vector<amyKeeper<amyArray>>& operator()();
typedef vector<amyKeeper<amyArray>> tData;
private:
	vector<amyKeeper<amyArray>> m_Data;
};