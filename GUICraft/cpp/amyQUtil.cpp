#include"amyQUtil.h"
#include<math.h>
#include<stdlib.h>
#include<QImage>
#include<QColor>
#include"amyDICOM.h"
#include"dcmtk\dcmimgle\dcmimage.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include"amyCube.h"
#include"itkImage.h"
#include"itkImageRegionConstIterator.h"
#include "dcmtk/dcmjpeg/djdecode.h" 
#include"amyTypeWrap.h"
#include<Qpainter>
namespace amyUtil
{
//
//QImage* GetSeriesThumb(amySeries* ser)
//{
//	int count=ser->slicearr.size();
//	string p=ser->slicearr[count/2]->info->filepath;
//	DcmFileFormat FileFormat;
//	OFCondition dcmCondition =FileFormat.loadFile(p.c_str());
//	DJDecoderRegistration::registerCodecs();
//	DcmDataset *dataset = FileFormat.getDataset();
//	E_TransferSyntax xfer = dataset->getOriginalXfer(); 
//	dataset->chooseRepresentation(xfer, NULL);
//
//	DicomImage *dcmimg=new DicomImage(p.c_str(),xfer  );
//	QImage* img;
//	int w=dcmimg->getWidth();
//	int h=dcmimg->getHeight();
//	QColor color;
//	void * pDicomDibits=0;
//	dcmimg->setWindow(ser->slicearr[0]->info->windowcenter,ser->slicearr[0]->info->windowwidth);
//	if (dcmimg->isMonochrome())
//	{
//		img=new QImage(w,h,QImage::Format_Indexed8);
//		img->setNumColors(256);
//		for (int i=0; i<256; i++) 
//		{
//			color.setRgb(i, i, i);
//			img->setColor(i, color.rgb());
//		}
//		dcmimg->createWindowsDIB(pDicomDibits, 0, 0, 8, 0, 1);
//		unsigned char * pd;
//		pd=(unsigned char *)pDicomDibits;
//		if(pDicomDibits)
//		memcpy(img->bits(),pDicomDibits,w*h);
//	}
//	else
//	{
//		uchar *px;
//		uchar pixel[4];
//		img=new QImage(w,h,QImage::Format_RGB32);
//		dcmimg->createWindowsDIB(pDicomDibits, 0, 0, 24, 0, 1);
//		unsigned char * pd;
//		pd=(unsigned char *)pDicomDibits;
//		if(pDicomDibits)
//		{
//			for (int y=0; y < (long) h; y++)
//			{
//				px = img->scanLine(y);
//				for (int x=0; x < (ulong) w; x++)
//				{
//					QRgb *row = (QRgb*) px;
//
//					pixel[2] = (unsigned char) (*(pd+3*y*w+3*x)); 
//					pixel[1] = (unsigned char) (*(pd+3*y*w+3*x+1)); 
//					pixel[0] = (unsigned char) (*(pd+3*y*w+3*x+2));
//
//					//pixel[3] = (unsigned char) (*pd++);
//
//					row[x] = qRgb(pixel[0], pixel[1], pixel[2]); 
//
//				}//for
//			}//for
//		}//if
//	}
//	DJDecoderRegistration::cleanup();
//	if(dcmimg)
//		delete dcmimg;
//	if(pDicomDibits)
//		delete pDicomDibits;
//	return img;
//}
QImage GetCubeThumb(amyCube* cube)
{
	typedef amyCube::tCube tInput;
	tInput::RegionType inputRegion =
		cube->obj->GetLargestPossibleRegion();
	tInput::SizeType size = inputRegion.GetSize();


	int imgwidth=size[0];
	int imgheight=size[1];
	int imgdepth=size[2];
	int m_WindowCenter=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowcenter:cube->windowcenter;
	int m_WindowWidth=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowwidth:cube->windowwidth;
	int min = (2*m_WindowCenter - m_WindowWidth)/2.0 + 0.5;
	int max = (2*m_WindowCenter + m_WindowWidth)/2.0 + 0.5;

	QImage m_Image=QImage(imgwidth,imgheight,QImage::Format_Indexed8);
	for (unsigned int i=0;i<256;i++)
	{
		QColor* rgb =new QColor(i,i,i);
		m_Image.setColor(i,rgb->rgb());
	}
	for (unsigned int i=0;i<imgwidth;i++)
	{
		for (unsigned int j=0;j<imgheight;j++)
		{
			amyCube::tCube::IndexType index;
			index[0]=i;
			index[1]=j;
			index[2]=imgdepth/2;
			short v=cube->obj->GetPixel(index);
			int   postv=(v - min)*255.0/(double)(max - min);
			unsigned char tv;
			if(postv<0) tv=0;
			else if(postv>255) tv=255;
			else tv=postv;
			m_Image.setPixel(i,j,tv);
		}
	}
	return m_Image;
}

//QImage GetFloatThumb(amyFloat* num)
//{
//	float v=num->value;
//	QImage image(64,64,QImage::Format_ARGB32);
//	QPainter p(&image);
//	p.fillRect(QRect(0,0,64,64),QColor(160,160,160));
//	p.drawText(QRect(0,0,64,64),Qt::AlignCenter,QString::number(v));
//	return image;
//}

//QImage GetCubeArrThumb(amyCubeArr* cubearr)
//{
//	QImage image(64,64,QImage::Format_Indexed8);
//	QPainter p(&image);
//	for(int i=0;i<cubearr->cubearr.size();i++)
//	{
//		if(i<=3)
//			p.drawImage(i*10,i*10,GetCubeThumb(cubearr->cubearr[i].GetPointer()).scaled(32,32));
//	}
//	return image;
//}

}//namespace