#include"amyCube.h"
#include "itkGDCMImageIO.h"
#include"amyDebug.h"
#include "amyDICOM.h"

#include "itkImageSeriesReader.h"
#include "itkImageDuplicator.h"
#include"amyUtil.h"
#include"amySeriesManager.h"
#include"itkDICOMImageIO2.h"
#include"itkRGBToLuminanceImageFilter.h"
#include"itkCastImageFilter.h"
#include"itkDicomImageIO.h"
#include"itkJPEG2000ImageIO.h"
bool amyCube::Open(amySeries::Keeper ser)
{
	if(ser->slicearr.size()==0)
		return 0;
	this->series=ser;
	typedef itk::GDCMImageIO                        ImageIOType;
	ImageIOType::Pointer dcmIO2 = ImageIOType::New();
	typedef itk::JPEG2000ImageIO JType;
	//JType::Pointer j=JType::New();
	//string debug=ser->slicearr[1]->info->filepath.c_str();
	if(dcmIO2->CanReadFile(ser->slicearr[0]->info->filepath.c_str()))
	{
		dcmIO2->SetFileName(ser->slicearr[0]->info->filepath.c_str());
		//dcmIO2->UpdateOutputData();
		dcmIO2->ReadImageInformation();
		typedef itk::ImageIOBase::IOComponentType CType;
		typedef itk::ImageIOBase::IOPixelType     PType;
		typedef itk::ImageIOBase::ByteOrder       BType;
		typedef itk::GDCMImageIO::TCompressionType CpType;
		CType ct=dcmIO2->GetComponentType();
		int n=dcmIO2->GetNumberOfComponents();
		BType bt=dcmIO2->GetByteOrder();
		PType pt=dcmIO2->GetPixelType();
		CpType Cpt=dcmIO2->GetCompressionType();
		if(n==1)
		{
			typedef itk::ImageSeriesReader<tCube> tReader;
			tReader::Pointer reader=tReader::New();
			reader->SetImageIO( dcmIO2 );
			for(int i=0;i<ser->slicearr.size();i++)
			{
				reader->AddFileName(ser->slicearr[i]->info->filepath);
			}
			try
			{
				reader->Update();
			}
			catch (itk::ExceptionObject &excp)
			{
				return 0;
			}
			obj=reader->GetOutput();
			this->windowcenter=ser->slicearr[0]->info->windowcenter;
			this->windowwidth=ser->slicearr[0]->info->windowwidth;
		}//if(n==1)
		if(n==3)
		{
			typedef itk::RGBPixel< unsigned char >   ucPixelType;
			typedef itk::Image<ucPixelType,3>        RGBCube;
			typedef itk::ImageSeriesReader<RGBCube>  tRGBReader;
			tRGBReader::Pointer reader=tRGBReader::New();
			reader->Register();
			reader->SetImageIO( dcmIO2 );
			//dcmIO2->SetCompressionType(itk::GDCMImageIO::JPEG2000);
			for(int i=0;i<ser->slicearr.size();i++)
			{
				reader->AddFileName(ser->slicearr[i]->info->filepath);
			}
			try
			{
				reader->Update();
			}
			catch (itk::ExceptionObject &excp)
			{
				return 0;
			}
			typedef itk::Image<unsigned char,3> ucCubeType;
			typedef itk::RGBToLuminanceImageFilter< RGBCube, ucCubeType >
				FilterType;
			FilterType::Pointer filter = FilterType::New();
			filter->SetInput( reader->GetOutput() );
			//filter->set
			try
			{
				filter->Update();
			}
			catch (itk::ExceptionObject &excp)
			{
				return 0;
			}
			typedef itk::CastImageFilter<ucCubeType,amyCube::tCube> CT;
			CT::Pointer ctf=CT::New();
			ctf->SetInput(filter->GetOutput());
			ctf->Update();
			obj=ctf->GetOutput();
			int wc=0,ww=0;
			amyUtil::GetWindowCenterWidth(this,wc,ww);
			this->windowcenter=wc;
			this->windowwidth=ww;
			this->series->slicearr[0]->info->windowcenter=wc;
			this->series->slicearr[0]->info->windowwidth=ww;
		}
	}


	return 1;
}
bool amyCube::Open(vector<string>& filearr)
{
	typedef itk::ImageSeriesReader<tCube> tReader;
	typedef itk::GDCMImageIO                        ImageIOType;
	tReader::Pointer reader=tReader::New();
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	for(int i=0;i<filearr.size();i++)
	{
		reader->SetImageIO( gdcmIO );
		reader->AddFileName(filearr[i]);
	}
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject &excp)
	{
		return 0;
	}
	obj=reader->GetOutput();
	return 1; 
}
void amyCube::Copy(amyCube* cube)
{
	typedef itk::ImageDuplicator< tCube > DuplicatorType;
	DuplicatorType::Pointer duplicator = DuplicatorType::New();
	duplicator->SetInputImage(cube->obj);
	duplicator->Update();
	this->obj = duplicator->GetOutput();
	this->windowcenter=cube->windowcenter;
	this->windowwidth=cube->windowwidth;
	this->series=cube->series;
}
void amyCube::SetObj(tCube::Pointer data)
{
	this->obj=data;
	amyUtil::GetWindowCenterWidth(this,this->windowcenter,this->windowwidth);
}
amyCube::~amyCube()
{
	amySeriesManager* sm=amySeriesManager::GetInstance();
	sm->DeleteCube(this);
}
//bool amyCube::Open(const char* filename)
//{
//	return 1;
//
//}
//bool amyCube::Open(amyDICOMSubseriesInfo* Subseries)
//{
//	for(int i=0;i<Subseries->ImageArr.size();i++)
//	{
//		DicomImage* pimg=new DicomImage(Subseries->ImageArr[i]->FilePath.c_str());
//		if(pimg->getStatus()==EIS_Normal)
//		{
//			this->m_ImageArr.push_back(pimg);
//		}
//		else
//		{
//			amyWarn("´ò¿ªÊ§°Ü%s",Subseries->ImageArr[i]->FilePath);
//			delete pimg;
//			return 0;
//		}
//	}
//	
//
//	return 1;
//
//}