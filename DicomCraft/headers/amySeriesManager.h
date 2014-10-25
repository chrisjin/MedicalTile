#pragma once
#include"amyPure.h"

#include"amyKeeper.h"
#include"amyWatcher.h"
#include"DicomMacro.h"
#define pSeriesManager (amySeriesManager::GetInstance())

class amyCube;
class amySeries;
class QImage;
class amySeriesManagerPrivate;


class  DICOM_INTERFACE amySeriesManager
{
	DEFINE_SINGLETON(amySeriesManager)
public:
	amySeriesManager();
	QImage*			   GetThumb(amySeries* ser);
	amyKeeper<amyCube> GetCube(amyWatcher<amySeries> ser);
	bool               HasCube(amyWatcher<amySeries> ser);
	void DeleteSeries(amySeries* ser);
	void DeleteCube(amyCube* cub);
private:
	amySeriesManagerPrivate* _d;
	
};