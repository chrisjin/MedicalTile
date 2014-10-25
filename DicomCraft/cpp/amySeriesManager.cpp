#include"amySeriesManager.h"
#include"amyCube.h"
#include"amyDICOM.h" 
#include<map>
#include"amyUtil.h"
#include<QImage>
#include"dcmtk\dcmimgle\dcmimage.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmjpeg/djdecode.h" 
#include "dcmtk/dcmimage/diregist.h"
#include<QColor>
using namespace std;
IMPLEMENT_SINGLETON(amySeriesManager)
class amySeriesManagerPrivate
{
public:
	map<amyWatcher<amySeries>,amyWatcher<amyCube>> m_Series2Cube;
	map<amySeries*,QImage*> m_Series2Thumb;
};
amySeriesManager::amySeriesManager()
{
	_d=new amySeriesManagerPrivate;
}
QImage* InnerGetSeriesThumb(amySeries* ser)
{
	int count=ser->slicearr.size();
	string p=ser->slicearr[count/2]->info->filepath;
	DcmFileFormat FileFormat;
	OFCondition dcmCondition =FileFormat.loadFile(p.c_str());
	DJDecoderRegistration::registerCodecs();
	DcmDataset *dataset = FileFormat.getDataset();
	E_TransferSyntax xfer = dataset->getOriginalXfer(); 
	dataset->chooseRepresentation(xfer, NULL);

	DicomImage *dcmimg=new DicomImage(p.c_str(),xfer  );
	if(dcmimg->getPhotometricInterpretation()==EPI_RGB)
	{
		//dcmimg=dcmimg->createMonoOutputImage(0,8);
	}
	float divw=float(dcmimg->getWidth());
	float divh=float(dcmimg->getHeight());
	if(divw==0||divh==0)
		return 0;
	float xra=64.0/divw;
	float yra=64.0/divh;

	DicomImage* oriimg=dcmimg;
	dcmimg=dcmimg->createScaledImage(xra,yra);

	delete oriimg;
	QImage* img;
	int w=dcmimg->getWidth();
	int h=dcmimg->getHeight();
	QColor color;
	void * pDicomDibits=0;
	dcmimg->setWindow(ser->slicearr[0]->info->windowcenter,ser->slicearr[0]->info->windowwidth);
	if (dcmimg->isMonochrome())
	{
		img=new QImage(w,h,QImage::Format_Indexed8);
		img->setNumColors(256);
		for (int i=0; i<256; i++) 
		{
			color.setRgb(i, i, i);
			img->setColor(i, color.rgb());
		}
		
		dcmimg->createWindowsDIB(pDicomDibits, 0, 0, 8, 0, 1);
		unsigned char * pd;
		pd=(unsigned char *)pDicomDibits;
		if(pDicomDibits)
		memcpy(img->bits(),pDicomDibits,w*h);
	}
	else
	{
		uchar *px;
		uchar pixel[4];
		img=new QImage(w,h,QImage::Format_RGB32);
		dcmimg->createWindowsDIB(pDicomDibits, 0, 0, 24, 0, 1);
		unsigned char * pd;
		pd=(unsigned char *)pDicomDibits;
		if(pDicomDibits)
		{
			for (int y=0; y < (long) h; y++)
			{
				px = img->scanLine(y);
				for (int x=0; x < (ulong) w; x++)
				{
					QRgb *row = (QRgb*) px;

					pixel[2] = (unsigned char) (*(pd+3*y*w+3*x)); 
					pixel[1] = (unsigned char) (*(pd+3*y*w+3*x+1)); 
					pixel[0] = (unsigned char) (*(pd+3*y*w+3*x+2));

					//pixel[3] = (unsigned char) (*pd++);

					row[x] = qRgb(pixel[0], pixel[1], pixel[2]); 

				}//for
			}//for
		}//if
	}
	DJDecoderRegistration::cleanup();
	if(dcmimg)
		delete dcmimg;
	if(pDicomDibits)
		delete pDicomDibits;
	return img;
}
QImage* amySeriesManager::GetThumb(amySeries* ser)
{
	map<amySeries*,QImage*>::iterator itr=_d->m_Series2Thumb.find(ser);
	typedef pair<amySeries*,QImage*> Pair;
	if(itr==_d->m_Series2Thumb.end())
	{

		QImage* image=InnerGetSeriesThumb( ser);
		this->_d->m_Series2Thumb.insert(Pair(ser,image));
		return  image;

	}
	else
	{
		if(itr->second)
		{
			return itr->second;
		}
		else
		{
			itr->second=InnerGetSeriesThumb(ser);
			return itr->second;
		}
	
	}
	
}
amyKeeper<amyCube>  amySeriesManager::GetCube(amyWatcher<amySeries> ser)
{
	map<amyWatcher<amySeries>,amyWatcher<amyCube>>::iterator itr=_d->m_Series2Cube.find(ser);
	typedef pair<amyWatcher<amySeries>,amyWatcher<amyCube>> Pair;
	if(_d->m_Series2Cube.end()==itr)
	{
		amyCube::Keeper keeper;
		keeper=amyCube::New();
		if(ser.HasKeeper())
		{
			if(0!=keeper->Open(ser.GetKeeper()))
				this->_d->m_Series2Cube.insert(Pair(ser,keeper));
		}
		return keeper;
	}
	else
	{
		if(itr->second.HasKeeper())
			return itr->second.GetKeeper();
		else
		{
			amyKeeper<amyCube> kcube=amyCube::New();
			kcube->Open(ser.GetKeeper());
			itr->second=kcube;
			return kcube;
		}
	}
}
bool amySeriesManager::HasCube(amyWatcher<amySeries> ser)
{
	map<amyWatcher<amySeries>,amyWatcher<amyCube>>::iterator itr=_d->m_Series2Cube.find(ser);
	if(_d->m_Series2Cube.end()==itr)
	{
		return 0;
	}
	else
	{
		if(itr->second.HasKeeper())
			return 1;
	}
	return 0;
}
void amySeriesManager::DeleteSeries(amySeries* ser)
{
	map<amyWatcher<amySeries>,amyWatcher<amyCube>>::iterator itr=_d->m_Series2Cube.begin();
	for(;itr!=_d->m_Series2Cube.end();itr++)
	{
		if(itr->first.GetPointer()==ser)
			break;
	}
	if(itr!=_d->m_Series2Cube.end())
		_d->m_Series2Cube.erase(itr);

	map<amySeries*,QImage*>::iterator thumbitr=_d->m_Series2Thumb.find(ser);
	if(thumbitr!=_d->m_Series2Thumb.end())
	{
		if(thumbitr->second)
			delete thumbitr->second;
		_d->m_Series2Thumb.erase(thumbitr);
	}
}

void amySeriesManager::DeleteCube(amyCube* cub)
{
	map<amyWatcher<amySeries>,amyWatcher<amyCube>>::iterator itr=_d->m_Series2Cube.begin();
	for(;itr!=_d->m_Series2Cube.end();itr++)
	{
		if(itr->second.GetPointer()==cub)
		{
			break;
		}
	}
	if(itr!=_d->m_Series2Cube.end())
	_d->m_Series2Cube.erase(itr);
}



