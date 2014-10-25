#include"amyCubeArrGenerator.h"
#include"amyAlgorithmStack.h"
#include"amyCube.h"
#include"amyDICOM.h"
#include"amySeriesManager.h"
#include"amySeriesSet.h"
#include"amyAlgorithmProgress.h"
#include<QRunnable>
#include<QThread>
#include<vector>
#include<QThreadPool>
#include"amyUtil.h"
using namespace std;
class RunRead:public QRunnable
{
public:
	RunRead(vector<int>* index,amySeriesSet::Keeper pserarr)
	{
		m_Index=index;
		m_SerSet=pserarr;
	}
	void run()
	{
		for(int i=0;i<m_Index->size();i++)
		{
			int index=m_Index->at(i);
			if(index>=0&&index<=m_SerSet->seriesarr.size())
			{
				amyCube::Keeper cu=amySeriesManager::GetInstance()->GetCube(m_SerSet->seriesarr[index]);
				amyUtil::Lock::GetInstance()->EnterCritical();
				m_SerSet->cubearr.push_back(cu);
				amyUtil::Lock::GetInstance()->LeaveCritical();
				pProgress->Step();
			}
		}
	}
private:
	vector<int>* m_Index;
	amySeriesSet::Keeper m_SerSet;
};
void  amyCubeArrGenerator::Run()
{
	amyVariable v=this->GetStack()->Pop();
	amySeriesSet::Keeper pserarr=v.Get<amySeriesSet>();


	pProgress->SetStepCount(pserarr->seriesarr.size());
	pProgress->Begin();

	//int threadcount=QThread::idealThreadCount();
	//vector<int>* indexarr=new vector<int>[threadcount];
	//for(int i=0;i<pserarr->seriesarr.size();i++)
	//{
	//	int pick=i%threadcount;
	//	indexarr[pick].push_back(i);
	//}
	//for(int i=0;i<threadcount;i++)
	//{
	//	RunRead* r=new RunRead(&indexarr[i],pserarr);
	//	QThreadPool::globalInstance()->start(r);
	//}
	//QThreadPool::globalInstance()->waitForDone();
	for(int i=0;i<pserarr->seriesarr.size();i++)
	{
		amyCube::Keeper cu=amySeriesManager::GetInstance()->GetCube(pserarr->seriesarr[i]);
		pserarr->cubearr.push_back(cu);
		pProgress->Step();
	}
	pProgress->End();
}