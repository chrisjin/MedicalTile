#include"amyDICOM.h"
#include"amySeriesManager.h"
amyPatient::~amyPatient()
{
	this->seriesarr.clear();
}

amySeries::~amySeries()
{
	amySeriesManager* sm=amySeriesManager::GetInstance();
	sm->DeleteSeries(this);
}

amySlice::~amySlice()
{

}