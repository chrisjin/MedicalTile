#pragma once
#include"amyAlgorithmPanel.h"
#include"amyAlgorithm.h"
class amyFormatEdit;
class GFRPanel:public amyAlgorithmPanel
{
	Q_OBJECT
public:
	GFRPanel(amyAlgorithm* a,QWidget* p=0);
	float space[3];
	float HCT;
	int T1;
	int T2;
public slots:
	void Update();
private:
	amyFormatEdit* m_Edit;
};