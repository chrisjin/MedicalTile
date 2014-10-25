//#include"amyProgress.h"
//#include"amyUtil.h"
//IMPLEMENT_SINGLETON(amyProgress)
//amyProgress::amyProgress()
//{
//	Reset();
//}
//void  amyProgress::SetValue(float a)
//{
//	if(a<=100)
//		m_Value=a;
//	else
//		m_Value=100;
//}
//float  amyProgress::GetValue()
//{
//	return m_Value;
//}
//void  amyProgress::SetStepNum(float a)
//{
//	m_StepNum=a;
//	m_ValuePerStep=100.0/(float)a+0.01;
//}
//void  amyProgress::Init(float stepnum)
//{
//	m_Value=0;
//	SetStepNum(stepnum);
//}
//void  amyProgress::Step()
//{
//	//amyUtil::Lock::GetInstance()->EnterCritical();
//	float a=m_Value+m_ValuePerStep;
//	if(a<=100)
//		m_Value=a;
//	else
//		m_Value=100;
//	//amyUtil::Lock::GetInstance()->LeaveCritical();
//}
//void  amyProgress::Reset()
//{
//	m_Value=0;
//	m_StepNum=0;
//	m_ValuePerStep=0;
//}