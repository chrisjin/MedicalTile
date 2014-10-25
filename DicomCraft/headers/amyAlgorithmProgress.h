#pragma once
#include"DicomMacro.h"
#include"amyPure.h"
#include<QObject>
#include<QMutex>
#define pProgress (amyAlgorithmProgress::GetInstance())
class DICOM_INTERFACE amyAlgorithmProgress:public QObject
{
	Q_OBJECT
	DEFINE_SINGLETON(amyAlgorithmProgress)
public:
	void SetStepCount(int a);
	void Step();
	void Begin();
	void End();
	int GetCurrentStep();
	int GetStepCount();
signals:
	void s_begin();
	void s_end();
	void s_step(int);
private:
	int m_StepCount;
	int m_CurrentStep;
	//QMutex m_Mutex;
};