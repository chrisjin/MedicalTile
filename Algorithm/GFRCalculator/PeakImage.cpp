#include"PeakImage.h"
#include"amySeriesSet.h"
#include"amyCube.h"
#include"amyAlgorithmStack.h"
#include"itkImageRegionIterator.h"
#include"amySeriesManager.h"
#include"amyAlgorithmProgress.h"
#include"itkDiscreteGaussianImageFilter.h"
#include"itkMeanImageFilter.h"
#include"itkMedianImageFilter.h"
#include"itkVersorRigid3DTransform.h"
#include "itkImageRegistrationMethod.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkVersorRigid3DTransform.h"
#include "itkCenteredTransformInitializer.h"
#include "itkVersorRigid3DTransformOptimizer.h"
#include"itkOrientImageFilter.h"
#include"itkMattesMutualInformationImageToImageMetric.h"
#include"itkBinomialBlurImageFilter.h"
#include"itkResampleImageFilter.h"
#include"itkGradientAnisotropicDiffusionImageFilter.h"
#include"amyAlgorithmProgress.h"
#include"itkCurvatureAnisotropicDiffusionImageFilter.h"
#include<QMessageBox>
amyCube::tCube::Pointer CubeTimeSequence::PreprocessCube(amyCube::tCube::Pointer p)
{
	return p;
}
amyCube::tCube::Pointer Registration(amyCube::tCube::Pointer o1,amyCube::tCube::Pointer o2)
{
		typedef itk::Image<float,3> CubeType;
	//typedef CubeType FixedImageType;
	//typedef CubeType MovingImageType;
	typedef itk::CastImageFilter<amyCube::tCube,CubeType> CastType;
	CastType::Pointer Cast1=CastType::New();
	CastType::Pointer Cast2=CastType::New();
	Cast1->SetInput(o1);
	Cast2->SetInput(o2);
	typedef itk::CurvatureAnisotropicDiffusionImageFilter<CubeType,CubeType> FilterType;
	FilterType::Pointer SF1=FilterType::New();
	FilterType::Pointer SF2=FilterType::New();
	SF1->SetInput(Cast1->GetOutput());
	SF2->SetInput(Cast2->GetOutput());
	SF1->SetConductanceParameter(3.0);
	SF1->SetTimeStep(0.0625);
	SF1->SetNumberOfIterations(5);
	SF2->SetConductanceParameter(3.0);
	SF2->SetTimeStep(0.0625);
	SF2->SetNumberOfIterations(5);
	SF1->Update();
	SF2->Update();
	CubeType::Pointer fo1=SF1->GetOutput();
	CubeType::Pointer fo2=SF2->GetOutput();
	CubeType::Pointer FImage=fo1;
	CubeType::Pointer MImage=fo2;
	/////////ARGS/////////////////////////////////////////////////
	int FixedImageSmoothingFactor=0;
	int MovingImageSmoothingFactor=0; 
	int HistogramBins=30;  //////FFFFF
	int SpatialSamples=10000.0;
	int Iterations=2000;
	int TranslationScale=100.0 ; //////FFFFFF
	
	
	
	string args="";
	args+="Smoothing level for fixed image:%d\n";
	args+="Smoothing level for Moving image:%d\n";
	args+="Histogram Bins:%d\n";
	args+="Spatial Samples:%d\n";
	args+="Iterations:%d\n";
	args+="Translation scalings:%d\n";
	//amyUtil::scanf(args.c_str(),&FixedImageSmoothingFactor,&MovingImageSmoothingFactor,
	//	&HistogramBins,&SpatialSamples,
	//	&Iterations,&TranslationScale);
  /////////ARGS/////////////////////////////////////////////////
  const    unsigned int ImageDimension = 3;
  typedef  float T1;
  typedef  T1                                        FixedPixelType; // ##
  typedef itk::Image<FixedPixelType, ImageDimension> FixedImageType; // ##

  typedef itk::OrientImageFilter<FixedImageType, FixedImageType> FixedOrientFilterType; // ##
  typedef  float T2;
  typedef  T2                                         MovingPixelType; // ##
  typedef itk::Image<MovingPixelType, ImageDimension> MovingImageType; // ##

  typedef itk::OrientImageFilter<MovingImageType, MovingImageType> MovingOrientFilterType; // ##

  typedef itk::MattesMutualInformationImageToImageMetric<FixedImageType, MovingImageType> MetricType;    // ##
  typedef itk::RegularStepGradientDescentOptimizer                                        OptimizerType;
  typedef itk::LinearInterpolateImageFunction<MovingImageType, double>                    InterpolatorType; // ##
  typedef itk::ImageRegistrationMethod<FixedImageType, MovingImageType>                   RegistrationType; // ##
  typedef itk::AffineTransform<double>                                                    TransformType;
  typedef OptimizerType::ScalesType                                                       OptimizerScalesType;
  typedef itk::ResampleImageFilter<MovingImageType, MovingImageType>                      ResampleType;             // ##
  typedef itk::LinearInterpolateImageFunction<MovingImageType, double>                    ResampleInterpolatorType; // ##            // ##
  typedef itk::ContinuousIndex<double, 3>                                                 ContinuousIndexType;

  FixedOrientFilterType::Pointer orientFixed = FixedOrientFilterType::New(); // ##
  orientFixed->UseImageDirectionOn();
  orientFixed->SetDesiredCoordinateOrientationToAxial();
  
  
  if( FixedImageSmoothingFactor != 0 )  ////FFFFF1
  {
	  typedef itk::BinomialBlurImageFilter<FixedImageType, FixedImageType> BinomialFixedType;
	  BinomialFixedType::Pointer BinomialFixed = BinomialFixedType::New();
	  BinomialFixed->SetInput(   FImage );
	  BinomialFixed->SetRepetitions( FixedImageSmoothingFactor * 2);
	  //itk::PluginFilterWatcher watchfilter(BinomialFixed, "Binomial Filter Fixed",  CLPProcessInformation, 1.0 / 5.0,
		 // 1.0 / 5.0);
	  BinomialFixed->Update();
	  orientFixed->SetInput(BinomialFixed->GetOutput() );
  }
  else
  {
	  orientFixed->SetInput(FImage );
  }
  orientFixed->Update();

  MovingOrientFilterType::Pointer orientMoving = MovingOrientFilterType::New(); // ##
    orientMoving->UseImageDirectionOn();
  orientMoving->SetDesiredCoordinateOrientationToAxial();

    ///FFFFFF
  if( MovingImageSmoothingFactor != 0 )
  {
	  typedef itk::BinomialBlurImageFilter<MovingImageType,  MovingImageType> BinomialMovingType;
	  BinomialMovingType::Pointer BinomialMoving = BinomialMovingType::New();
	  BinomialMoving->SetInput(   MImage );
	  BinomialMoving->SetRepetitions( MovingImageSmoothingFactor * 2);
	  //itk::PluginFilterWatcher watchfilter(BinomialMoving, "Binomial Filter Moving",  CLPProcessInformation, 1.0 / 5.0,
		 // 3.0 / 5.0);
	  BinomialMoving->Update();
	  orientMoving->SetInput(BinomialMoving->GetOutput() );
  }
  else
  {
	  orientMoving->SetInput(MImage );
  }
  orientMoving->Update();

  
  OptimizerType::Pointer      optimizer     = OptimizerType::New();
  optimizer->SetNumberOfIterations( Iterations );
  optimizer->SetMinimumStepLength( .0005 );
  optimizer->SetMaximumStepLength( 10.0 );
  optimizer->SetMinimize(true);

  
  TransformType::Pointer transform = TransformType::New();
  OptimizerScalesType scales( transform->GetNumberOfParameters() );
  scales.Fill( 1.0 );
  for( unsigned j = 9; j < 12; j++ )
  {
	  scales[j] = 1.0 / vnl_math_sqr(TranslationScale);
  }
  optimizer->SetScales( scales );

  TransformType::InputPointType centerFixed;
  FixedImageType::RegionType::SizeType sizeFixed =
	  orientFixed->GetOutput()->GetLargestPossibleRegion().GetSize();

  ContinuousIndexType indexFixed;
  for( unsigned j = 0; j < 3; j++ )
  {
	  indexFixed[j] = (sizeFixed[j] - 1) / 2.0;
  }
  orientFixed->GetOutput()->TransformContinuousIndexToPhysicalPoint( indexFixed, centerFixed );

  TransformType::InputPointType centerMoving;
  MovingImageType::RegionType::SizeType sizeMoving =
	  orientMoving->GetOutput()->GetLargestPossibleRegion().GetSize();
  // Find the center
  ContinuousIndexType indexMoving;
  for( unsigned j = 0; j < 3; j++ )
  {
	  indexMoving[j] = (sizeMoving[j] - 1) / 2.0;
  }
  orientMoving->GetOutput()->TransformContinuousIndexToPhysicalPoint( indexMoving, centerMoving );

  transform->SetCenter( centerFixed );
  transform->Translate(centerMoving - centerFixed);

  //////¶ÁÎÄ¼þ
  //if( InitialTransform != ""
	 // && initialTransform->GetTransformList()->size() != 0 )
  //{
	 // TransformReaderType::TransformType::Pointer initial
		//  = *(initialTransform->GetTransformList()->begin() );

	 // // most likely, the transform coming in is a subclass of
	 // // MatrixOffsetTransformBase
	 // typedef itk::MatrixOffsetTransformBase<double, 3, 3> DoubleMatrixOffsetType;
	 // typedef itk::MatrixOffsetTransformBase<float, 3, 3>  FloatMatrixOffsetType;

	 // DoubleMatrixOffsetType::Pointer da
		//  = dynamic_cast<DoubleMatrixOffsetType *>(initial.GetPointer() );
	 // FloatMatrixOffsetType::Pointer fa
		//  = dynamic_cast<FloatMatrixOffsetType *>(initial.GetPointer() );

	 // if( da )
	 // {
		//  transform->SetMatrix( da->GetMatrix() );
		//  transform->SetOffset( da->GetOffset() );
	 // }
	 // else if( fa )
	 // {
		//  vnl_matrix<double> t(3, 3);
		//  for( int i = 0; i < 3; ++i )
		//  {
		//	  for( int j = 0; j < 3; ++j )
		//	  {
		//		  t.put(i, j, fa->GetMatrix().GetVnlMatrix().get(i, j) );
		//	  }
		//  }

		//  transform->SetMatrix( t );
		//  transform->SetOffset( fa->GetOffset() );
	 // }
	 // else
	 // {
		//  std::cout << "Initial transform is an unsupported type." << std::endl;
	 // }

	 // std::cout << "Initial transform: "; transform->Print( std::cout );
  //}

  MetricType::Pointer  metric        = MetricType::New();
  metric->SetNumberOfHistogramBins( HistogramBins );
  metric->SetNumberOfSpatialSamples( SpatialSamples );
  metric->ReinitializeSeed(123);

  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  // Set up the registration
  //
  RegistrationType::Pointer registration = RegistrationType::New();
  registration->SetTransform( transform );
  registration->SetInitialTransformParameters( transform->GetParameters() );
  registration->SetMetric( metric );
  registration->SetOptimizer( optimizer );
  registration->SetInterpolator( interpolator );
  registration->SetFixedImage( orientFixed->GetOutput() );
   registration->SetMovingImage( orientMoving->GetOutput() );

   try
   {
	   registration->Update();
	   std::cout << "Optimizer stop condition: "
		   << registration->GetOptimizer()->GetStopConditionDescription()
		   << std::endl;
   }
   catch( itk::ExceptionObject & err )
   {
	   std::cerr << "ExceptionObject caught !" << std::endl;
	   std::cerr << err << std::endl;
	   return 0;
   }
   transform->SetParameters( registration->GetLastTransformParameters() );
   ResampleType::Pointer resample = ResampleType::New();
   ResampleInterpolatorType::Pointer Interpolator = ResampleInterpolatorType::New();
   //itk::PluginFilterWatcher watchResample(resample,
	  // "Resample",
	  // CLPProcessInformation,
	  // 1.0 / 5.0, 4.0 / 5.0);

   resample->SetInput( MImage );
   resample->SetTransform( transform );
   resample->SetInterpolator( Interpolator );

   MovingImageType::Pointer fixedInformation = MovingImageType::New();
   fixedInformation->CopyInformation( FImage);
   resample->SetOutputParametersFromImage( fixedInformation );

   resample->Update();



	typedef itk::CastImageFilter< FixedImageType, amyCube::tCube > CastFilterType;
	CastFilterType::Pointer  caster =  CastFilterType::New();
	caster->SetInput( resample->GetOutput() );
	caster->Update();

	return caster->GetOutput();
}

void CubeTimeSequence::Run()
{
	amyVariable v1=this->GetStack()->Pop();
	FETCH(amySeriesSet,set,v1);
	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);

	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
	retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
	retcube->SetSpacing(cubeobj->obj->GetSpacing());
	retcube->Allocate();

	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
	vector<CItrType> ItrArr;
	vector<amyCube::Keeper> PreventFromReleasing;
	vector<amyCube::tCube::Pointer> Fuck;
	typedef itk::MeanImageFilter<amyCube::tCube,amyCube::tCube> GF;

	//pProgress->SetStepCount(set.seriesarr.size());
	//pProgress->Begin();

	//amyCube::Keeper kcubetoregis=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);
	//Fuck.push_back(kcubetoregis->obj);
	for(int i=0;i<set.seriesarr.size();i++)
	{
		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
		PreventFromReleasing.push_back(kcube);
		amyCube::tCube::Pointer pcube=PreprocessCube(kcube->obj);

		//amyCube::tCube::Pointer afterregist;
		//if(i!=0)
		//{
		//	afterregist=Registration(kcubetoregis->obj,pcube);
		//}
		//else
		//{
		//	afterregist=pcube;
		//}
		//if(afterregist.IsNull())
		//{
		//	char text[100];
		//	sprintf(text,"%d Regisatration Error",i+1);
		//	this->PostError(text);
		//	pProgress->End();
		//}
		//pProgress->Step();
		ItrArr.push_back(CItrType(pcube,pcube->GetLargestPossibleRegion()));
		//ItrArr.push_back(CItrType(afterregist,afterregist->GetLargestPossibleRegion()));
		//Fuck.push_back(afterregist);


		//GF::Pointer f=GF::New();
		//f->SetInput(kcube->obj);
		//amyCube::tCube::SizeType size;
		//size[0]=1;
		//size[1]=1;
		//size[2]=1;
		//f->SetRadius(size);
		//f->Update();
		//Fuck.push_back(afterregist);
		//ItrArr.push_back(CItrType(f->GetOutput(),f->GetOutput()->GetLargestPossibleRegion()));
	}
//	pProgress->End();
	
	QMessageBox::information(0,"..","Registration Done");
	ItrType ItrRet(retcube,retcube->GetLargestPossibleRegion());
	while(1)
	{
		if(ItrRet.IsAtEnd())
			break;
		vector<int>  arrforonepixel;
		for(int i=0;i<ItrArr.size();i++)
		{
			arrforonepixel.push_back(ItrArr[i].Get());
		}
		int peak;
		int set=ForVoxTimeSequence(arrforonepixel);
		ItrRet.Set(set);
		for(int i=0;i<ItrArr.size();i++)
		{
			++ItrArr[i];
		}
		++ItrRet;
	}

	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Peak");
	FETCH(amyCube,ccc,ret);
	ccc.SetObj(retcube);
	this->GetStack()->Push(ret);
}




int   FindPeak(const vector<int>& arr,int& peak)
{
	int sum=-1000000;
	int ret;
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]>sum)
		{
			sum=arr[i];
			peak=sum;
			ret=i;
		}
	}
	return ret;
}
double   FindHalfPeak(const vector<int>& arr)
{
	int peak;
	FindPeak(arr,peak);
	double halfpeak=double(peak)/3.0*2.0;
	int index;
	for(index=1;index<arr.size();index++)
	{
		bool flag1=arr[index-1]<=halfpeak&&arr[index]>=halfpeak;
		bool flag2=arr[index-1]>=halfpeak&&arr[index]<=halfpeak;
		if(flag1||flag2)
		{
			break;
		}
	}
	if(index==arr.size())
		index=arr.size()-1;
	double div=arr[index]-arr[index-1];
	double ret;
	if(div!=0)
		ret=index-1+double(halfpeak-arr[index-1])/div;
	else
		ret=index-1;
	return index-1;
}
float  PeakImage::ForVoxTimeSequence(vector<int>& arr)
{
	int peak;
	int set=FindPeak(arr,peak);
	return set;
}
//void  PeakImage::Run()
//{
//	amyVariable v1=this->GetStack()->Pop();
//	FETCH(amySeriesSet,set,v1);
//	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);
//
//	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
//	retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
//	retcube->SetSpacing(cubeobj->obj->GetSpacing());
//	retcube->Allocate();
//
//	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
//	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
//	vector<CItrType> ItrArr;
//	vector<amyCube::Keeper> PreventFromReleasing;
//	vector<amyCube::tCube::Pointer> Fuck;
//	typedef itk::MeanImageFilter<amyCube::tCube,amyCube::tCube> GF;
//	for(int i=0;i<set.seriesarr.size();i++)
//	{
//		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
//		PreventFromReleasing.push_back(kcube);
//		ItrArr.push_back(CItrType(kcube->obj,kcube->obj->GetLargestPossibleRegion()));
//		
//		//GF::Pointer f=GF::New();
//		//f->SetInput(kcube->obj);
//		//amyCube::tCube::SizeType size;
//		//size[0]=1;
//		//size[1]=1;
//		//size[2]=1;
//		//f->SetRadius(size);
//		//f->Update();
//		//Fuck.push_back(f->GetOutput());
//		//ItrArr.push_back(CItrType(f->GetOutput(),f->GetOutput()->GetLargestPossibleRegion()));
//	}
//	
//	
//	
//	ItrType ItrRet(retcube,retcube->GetLargestPossibleRegion());
//	while(1)
//	{
//		if(ItrRet.IsAtEnd())
//			break;
//		vector<int>  arrforonepixel;
//		for(int i=0;i<ItrArr.size();i++)
//		{
//			arrforonepixel.push_back(ItrArr[i].Get());
//		}
//		int peak;
//		int set=FindPeak(arrforonepixel,peak);
//		ItrRet.Set(set);
//		for(int i=0;i<ItrArr.size();i++)
//		{
//			++ItrArr[i];
//		}
//		++ItrRet;
//	}
//
//	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Peak");
//	FETCH(amyCube,ccc,ret);
//	ccc.SetObj(retcube);
//	this->GetStack()->Push(ret);
//}

//float  PeakImageWithFactors::ForVoxTimeSequence(vector<int>& arr)
//{
//
//}
//void   PeakImageWithFactors::Run()
//{
//	amyVariable v1=this->GetStack()->Pop();
//	FETCH(amySeriesSet,set,v1);
//	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);
//
//	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
//	retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
//	retcube->SetSpacing(cubeobj->obj->GetSpacing());
//	retcube->Allocate();
//
//	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
//	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
//	vector<CItrType> ItrArr;
//	vector<amyCube::Keeper> PreventFromReleasing;
//	vector<amyCube::tCube::Pointer> Fuck;
//	typedef itk::MeanImageFilter<amyCube::tCube,amyCube::tCube> GF;
//	for(int i=0;i<set.seriesarr.size();i++)
//	{
//		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
//		PreventFromReleasing.push_back(kcube);
//		//ItrArr.push_back(CItrType(kcube->obj,kcube->obj->GetLargestPossibleRegion()));
//
//		GF::Pointer f=GF::New();
//		f->SetInput(kcube->obj);
//		amyCube::tCube::SizeType size;
//		size[0]=1;
//		size[1]=1;
//		size[2]=1;
//		f->SetRadius(size);
//		f->Update();
//		Fuck.push_back(f->GetOutput());
//		ItrArr.push_back(CItrType(f->GetOutput(),f->GetOutput()->GetLargestPossibleRegion()));
//	}
//
//
//
//	ItrType ItrRet(retcube,retcube->GetLargestPossibleRegion());
//	while(1)
//	{
//		if(ItrRet.IsAtEnd())
//			break;
//		vector<int>  arrforonepixel;
//		for(int i=0;i<ItrArr.size()&&i<=10;i++)
//		{
//			arrforonepixel.push_back(ItrArr[i].Get());
//		}
//		int peak;
//		int set=FindPeak(arrforonepixel,peak);
//		//ItrRet.Set(set/float(abs(peak)+1));
//		ItrRet.Set(set);
//		for(int i=0;i<ItrArr.size();i++)
//		{
//			++ItrArr[i];
//		}
//		++ItrRet;
//	}
//
//	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Peak");
//	FETCH(amyCube,ccc,ret);
//	ccc.SetObj(retcube);
//	this->GetStack()->Push(ret);
//}
float  HalfPeakImage::ForVoxTimeSequence(vector<int>& arr)
{
	return FindHalfPeak(arr);
}
int FindDiffSum(vector<int>& arr)
{
	int sum=0;
	for(int i=1;i<arr.size();i++)
	{
		sum+=arr[i]-arr[i-1];
	}
	return sum;
}
float  PeakMulTimeImage::ForVoxTimeSequence(vector<int>& arr)
{
	int peak;
	int set=FindPeak(arr,peak);
	return set*peak;

//	return FindDiffSum(arr);
}

float  SumImage::ForVoxTimeSequence(vector<int>& arr)
{
	int peak;
	int set=FindPeak(arr,peak);
	int sum=0;
	for(int i=0;i<=set;i++)
	{
		sum+=arr[i];
	}
	return sum;
}


//void   HalfPeakImage::Run()
//{
//	amyVariable v1=this->GetStack()->Pop();
//	FETCH(amySeriesSet,set,v1);
//	amyCube::Keeper cubeobj=amySeriesManager::GetInstance()->GetCube(set.seriesarr[0]);
//
//	amyCube::tCube::Pointer retcube=amyCube::tCube::New();
//	retcube->SetRegions(cubeobj->obj->GetLargestPossibleRegion());
//	retcube->SetSpacing(cubeobj->obj->GetSpacing());
//	retcube->Allocate();
//
//	typedef itk::ImageRegionConstIterator<amyCube::tCube> CItrType;
//	typedef itk::ImageRegionIterator<amyCube::tCube>      ItrType;
//	vector<CItrType> ItrArr;
//	vector<amyCube::Keeper> PreventFromReleasing;
//	vector<amyCube::tCube::Pointer> Fuck;
//	typedef itk::MeanImageFilter<amyCube::tCube,amyCube::tCube> GF;
//	for(int i=0;i<set.seriesarr.size();i++)
//	{
//		amyCube::Keeper kcube=amySeriesManager::GetInstance()->GetCube(set.seriesarr[i]);
//		PreventFromReleasing.push_back(kcube);
//		ItrArr.push_back(CItrType(kcube->obj,kcube->obj->GetLargestPossibleRegion()));
//
//		//GF::Pointer f=GF::New();
//		//f->SetInput(kcube->obj);
//		//amyCube::tCube::SizeType size;
//		//size[0]=1;
//		//size[1]=1;
//		//size[2]=1;
//		//f->SetRadius(size);
//		//f->Update();
//		//Fuck.push_back(f->GetOutput());
//		//ItrArr.push_back(CItrType(f->GetOutput(),f->GetOutput()->GetLargestPossibleRegion()));
//	}
//
//
//
//	ItrType ItrRet(retcube,retcube->GetLargestPossibleRegion());
//	while(1)
//	{
//		if(ItrRet.IsAtEnd())
//			break;
//		vector<int>  arrforonepixel;
//		for(int i=0;i<ItrArr.size();i++)
//		{
//			arrforonepixel.push_back(ItrArr[i].Get());
//		}
//		int peak;
//		double set=FindHalfPeak(arrforonepixel);
//		//ItrRet.Set(set/float(abs(peak)+1));
//		ItrRet.Set(short(set));
//		for(int i=0;i<ItrArr.size();i++)
//		{
//			++ItrArr[i];
//		}
//		++ItrRet;
//	}
//
//	amyVariable ret=amyVariable::New(VTYPE_CUBE,"Peak");
//	FETCH(amyCube,ccc,ret);
//	ccc.SetObj(retcube);
//	this->GetStack()->Push(ret);
//}