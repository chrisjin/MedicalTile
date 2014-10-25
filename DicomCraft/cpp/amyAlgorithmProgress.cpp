#include"amyAlgorithmProgress.h"
#include<QEventLoop>
#include<QApplication>
IMPLEMENT_SINGLETON(amyAlgorithmProgress)

void amyAlgorithmProgress::SetStepCount(int a)
{
	m_StepCount=a;
}
void amyAlgorithmProgress::Step()
{
	if(this->thread()!=QApplication::instance()->thread())
	{
		this->moveToThread(QApplication::instance()->thread());
	}
	//m_Mutex.lock();
	m_CurrentStep++;
	emit s_step(m_CurrentStep);
	//m_Mutex.unlock();
}
void amyAlgorithmProgress::Begin()
{
	m_CurrentStep=0;
	emit s_begin();
}
void amyAlgorithmProgress::End()
{
	emit s_end();
	m_CurrentStep=0;
	m_StepCount=0;
}

int amyAlgorithmProgress::GetCurrentStep()
{
	return m_CurrentStep;
}
int amyAlgorithmProgress::GetStepCount()
{
	return m_StepCount;
}