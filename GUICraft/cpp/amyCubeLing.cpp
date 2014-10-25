#include"amyCubeLing.h"
#include"amyCube.h"
#include<qimage.h>
#include<qcolor.h>
#include<qpixmap.h>
#include<qpainter.h>
#include"amyCanvas.h"
#include "itkExtractImageFilter.h"
#include"amyDebug.h"
#include"amyAnnotationLing.h"
#include<QApplication>
#include"itkImageRegionConstIterator.h"
#include"amyDICOM.h"
#include"amyUtil.h"
#include"itkAffineTransform.h"
#include"itkResampleImageFilter.h"
#include"itkNearestNeighborInterpolateImageFunction.h"

static QPoint LastPoint;
amyCubeLing::amyCubeLing(amyCanvas* can):amyZoomLing(can)
{

	m_Slice=0;
	m_WindowWidth=250;
	m_WindowCenter=50;
	this->SetInput(0);
	m_IsCtrlLock=0;
}
#define SWAP(type,a,b)\
{\
	type i=a;\
	a=b;\
	b=i;\
}
void amyCubeLing::InitInput()
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	emit s_inputchanged();
	amyZoomLing::InitInput();
	m_InputRegion=cube->obj->GetLargestPossibleRegion();
	//ComputeSliceSizeFromView();
	////cube->obj->get
	//typedef amyCube::tCube tInput;
	//typedef itk::ResampleImageFilter<amyCube::tCube,amyCube::tCube> RFType;
	//typedef itk::AffineTransform<double,3>                          TType;
	//  typedef itk::NearestNeighborInterpolateImageFunction<
	//	                                  amyCube::tCube, double >  IType;
	//
	//TType::Pointer  T=TType::New();
	////TType::OutputVectorType axial;
	////axial[0]=0;
	////axial[1]=1;
	////axial[2]=0;
	////const double degreesToRadians = vcl_atan(1.0) / 45.0;
	////T->Rotate3D(axial,90*degreesToRadians);
	//T->SetMatrix(cube->obj->GetInverseDirection());
	//IType::Pointer I=IType::New();

	//RFType::Pointer RF=RFType::New();
	//RF->SetTransform(T);
	//RF->SetInterpolator(I);
	//RF->SetOutputOrigin(cube->obj->GetOrigin());
	//amyCube::tCube::SpacingType spacing=cube->obj->GetSpacing();
	//SWAP(double,spacing[1],spacing[2])
	//RF->SetOutputSpacing(spacing);
	//amyCube::tCube::RegionType oriregion=cube->obj->GetLargestPossibleRegion();
	//amyCube::tCube::SizeType   orisize=oriregion.GetSize();
	//SWAP(double,orisize[1],orisize[2]);
	//RF->SetSize(orisize);
	//RF->SetInput(cube->obj);
	//RF->Update();
	//cube->obj=RF->GetOutput();
	////m_Cube=RF->GetOutput();
	//amyCube::tCube::DirectionType d=cube->obj->GetDirection();
	//m_InputRegion =
	//	cube->obj->GetLargestPossibleRegion();
	//amyCube::tCube::SizeType size = m_InputRegion.GetSize();
	//int imgwidth=size[0];
	//int imgheight=size[1];
	int c=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowcenter:cube->windowcenter;
	int w=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowwidth:cube->windowwidth;
	m_WindowWidth=w;
	m_WindowCenter=c;
	amyUtil::GetCubeMinMax(cube,this->GetSlice(),this->m_DensityMin,this->m_DensityMax);
	//this->SetView(amyUtil::AXIAL);
	this->SetView(amyUtil::GetPlaneType(cube));


}

void amyCubeLing::ComputeSliceSizeFromView()
{
	if(this->GetInputView()==amyUtil::AXIAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[0];
			m_SliceHeight=size[1];
			m_SliceNum=size[2];
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[0];
			m_SliceHeight=size[2];
			m_SliceNum=size[1];
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[1];
			m_SliceHeight=size[2];
			m_SliceNum=size[0];
		}
	}
	if(this->GetInputView()==amyUtil::CORONAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[0];
			m_SliceHeight=size[2];
			m_SliceNum=size[1];
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[0];
			m_SliceHeight=size[1];
			m_SliceNum=size[2];
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[2];
			m_SliceHeight=size[1];
			m_SliceNum=size[0];
		}
	}
	if(this->GetInputView()==amyUtil::SAGITTAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[2];
			m_SliceHeight=size[0];
			m_SliceNum=size[1];
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[2];
			m_SliceHeight=size[1];
			m_SliceNum=size[0];
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			amyCube::tCube::SizeType size=m_InputRegion.GetSize();
			m_SliceWidth=size[0];
			m_SliceHeight=size[1];
			m_SliceNum=size[2];
		}
	}
}
amyCubeLing::ItrType amyCubeLing::ComputeIteratorFromView()
{
	amyCube::tCube ::SizeType size = m_InputRegion.GetSize();
	amyCube::tCube::IndexType index= m_InputRegion.GetIndex();
	
	amyCube::tCube::RegionType region;
	if(this->GetInputView()==amyUtil::AXIAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			size[2]=1;
			index[2]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(0);
			itr.SetSecondDirection(1);
			return itr;
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			size[1]=1;
			index[1]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(0);
			itr.SetSecondDirection(2);
			return itr;
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			size[0]=1;
			index[0]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(1);
			itr.SetSecondDirection(2);
			return itr;
		}
	}
	if(this->GetInputView()==amyUtil::CORONAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			size[1]=1;
			index[1]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(0);
			itr.SetSecondDirection(2);
			return itr;
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			size[2]=1;
			index[2]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(0);
			itr.SetSecondDirection(1);
			return itr;
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			size[0]=1;
			index[0]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(2);
			itr.SetSecondDirection(1);
			return itr;
		}
	}
	if(this->GetInputView()==amyUtil::SAGITTAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			size[1]=1;
			index[1]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			amyCube::tCube::Pointer p=this->GetInput()->obj;
			ItrType itr(p,region);
			itr.SetFirstDirection(2);
			itr.SetSecondDirection(0);
			return itr;
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			size[0]=1;
			index[0]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(2);
			itr.SetSecondDirection(1);
			return itr;
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			size[2]=1;
			index[2]=GetSlice();
			region.SetSize(size);
			region.SetIndex(index);
			ItrType itr(this->GetInput()->obj,region);
			itr.SetFirstDirection(0);
			itr.SetSecondDirection(1);
			return itr;
		}
	}
}
void amyCubeLing::InitImage(QImage& image)
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	ComputeSliceSizeFromView();
	//amyCube::tCube::SizeType size = m_InputRegion.GetSize();
	int imgwidth=m_SliceWidth;
	int imgheight=m_SliceHeight;
	image=QImage(imgwidth,imgheight,QImage::Format_Indexed8);
	for (unsigned int i=0;i<256;i++)
	{
		QColor rgb =QColor(i,i,i);
		image.setColor(i,rgb.rgb());
	}
	amyZoomLing::InitImage(image);
}
void amyCubeLing::UpdateImage(QImage& image)
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	//amyCube::tCube ::SizeType size = m_InputRegion.GetSize();
	//amyCube::tCube::IndexType index=m_InputRegion.GetIndex();

	//int imgwidth =m_SliceWidth;
	//int imgheight=m_SliceHeight;
	//int imgheight =m_SliceWidth;
	//int imgwidth=m_SliceHeight;
	int min = (2*m_WindowCenter - m_WindowWidth)/2.0 + 0.5;
	int max = (2*m_WindowCenter + m_WindowWidth)/2.0 + 0.5;
	
	//amyCube::tCube::RegionType region=this->ComputeCubeRegionFromView();
	//size[2]=1;
	//index[2]=GetSlice();
	//region.SetIndex(index);
	//region.SetSize(size);
	ItrType Itr=this->ComputeIteratorFromView();
	//typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;
	//ItrType Itr(cube->obj,region);
	//Itr.SetFirstDirection(0);
	//Itr.SetSecondDirection(2);
	unsigned char* imagedata=image.bits();
	int width=image.width();
	int res=width%4;
	int padding=4-(res?res:4);
	int i=0;
	int linenum=0;
	while (!Itr.IsAtEnd())
	{
		while (!Itr.IsAtEndOfSlice())
		{
			linenum=0;
			while(!Itr.IsAtEndOfLine())
			{
				short v=Itr.Get();
				int   postv=(v - min)*255.0/(double)(max - min);
				unsigned char tv;
				if(postv<0) tv=0;
				else if(postv>255) tv=255;
				else tv=postv;
				*(imagedata+i)=tv;
				++Itr;
				++i;
				linenum++;
			}
			i+=padding;
			Itr.NextLine();
		}
		Itr.NextSlice();
	}
	//for(Itr.GoToBegin(),i=0;!Itr.IsAtEnd()&&i<image.byteCount();++Itr,++i)
	//{
	//	short v=Itr.Get();
	//	int   postv=(v - min)*255.0/(double)(max - min);
	//	unsigned char tv;
	//	if(postv<0) tv=0;
	//	else if(postv>255) tv=255;
	//	else tv=postv;
	//	*(imagedata+i)=tv;
	//}
	AdjustImageDirectionFromView(image);
	this->GetCanvas()->repaint();
}
void    amyCubeLing::AdjustImageDirectionFromView(QImage& img)
{
	if(this->GetInputView()==amyUtil::AXIAL)
	{
		if(this->GetView()==amyUtil::CORONAL)
		{
			img=img.mirrored();
		}
		else if(this->GetView()==amyUtil::SAGITTAL)
		{
			img=img.mirrored();
		}
	}
	if(this->GetInputView()==amyUtil::CORONAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			img=img.mirrored();
		}
		else if(this->GetView()==amyUtil::SAGITTAL)
		{
			img=img.mirrored(1,0);
		}
	}
}
void amyCubeLing::SetWindow(int c,int w)
{
	m_WindowWidth=w;
	m_WindowCenter=c;
	Update();
}
int  amyCubeLing::GetSliceNum()
{
	return m_SliceNum;
}
int  amyCubeLing::GetSliceWidth()
{
	return m_SliceWidth;
}
int  amyCubeLing::GetSliceHeight()
{
	return m_SliceHeight;
}
int  amyCubeLing::GetSlice()
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return 0;
	//amyCube::tCube::SizeType size = m_InputRegion.GetSize();
	if(m_Slice<0)return 0;
	else if(m_Slice>m_SliceNum-1)return m_SliceNum-1;
	else return m_Slice;
}
void amyCubeLing::SetSlice(int s)
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	if(s==m_Slice)
		return;
	//amyCube::tCube::SizeType size = m_InputRegion.GetSize();
	//switch(m_View)
	//{
	//case VIEW_DEFAULT:
	if(s<0)s=0;
	if(s>m_SliceNum-1)s=m_SliceNum-1;
	//}
	amyUtil::GetCubeMinMax(cube,s,m_DensityMin,m_DensityMax);
	m_Slice=s;
	emit s_slicechanging(s);
	Update();
}
void amyCubeLing::mousePressEvent(QMouseEvent *event)
{
	int flag=1;
	if(IsCtrlLock())
	{
		flag=flag&&(QApplication::keyboardModifiers () == Qt::ControlModifier);
	}
	if(event->button()==Qt::RightButton&&flag)
	{
		if(this->GetCanvas()->cursor().shape()==Qt::ArrowCursor)
			this->GetCanvas()->setCursor(Qt::PointingHandCursor);
		SetMode(amyCubeLing::MODE_WINDOW);
		LastPoint = event->pos();
	}
	if(event->button()==Qt::LeftButton&&flag)
	{
		if(this->GetCanvas()->cursor().shape()==Qt::ArrowCursor)	
			this->GetCanvas()->setCursor(Qt::OpenHandCursor);
		SetMode(amyCubeLing::MODE_SLICE);
		LastPoint = event->pos();
	}
	amyZoomLing::mousePressEvent(event);
}
void amyCubeLing::mouseReleaseEvent(QMouseEvent *event)
{
	if(this->GetMode()!=MODE_NULL&&
		(this->GetCanvas()->cursor().shape()==Qt::SizeAllCursor)
		||(this->GetCanvas()->cursor().shape()==Qt::OpenHandCursor)
		||(this->GetCanvas()->cursor().shape()==Qt::PointingHandCursor))
		this->GetCanvas()->setCursor(Qt::ArrowCursor);
	this->SetMode(MODE_NULL);
	amyZoomLing::mouseReleaseEvent(event);
}
void amyCubeLing::mouseMoveEvent(QMouseEvent * event)
{
	QPoint CurrentPoint;
	if((event->buttons()&Qt::RightButton)&&GetMode()==MODE_WINDOW)
	{
		CurrentPoint= event->pos();
		double xvalue=LastPoint.x()-CurrentPoint.x();
		double yvalue=LastPoint.y()-CurrentPoint.y();
		int step=(m_DensityMax-m_DensityMin)/100;
		if(step==0)
			step=1;
		int windowcenter=this->m_WindowCenter+(+yvalue/3)*step;
		int windowwidth=this->m_WindowWidth+(-xvalue/3)*step;
		if(windowcenter>m_DensityMax)
			windowcenter=m_DensityMax;
		if(windowcenter<m_DensityMin)
			windowcenter=m_DensityMin;
		if(windowwidth>m_DensityMax)
			windowwidth=m_DensityMax;
		if(windowwidth<m_DensityMin)
			windowwidth=m_DensityMin;
		this->SetWindow(windowcenter,windowwidth);
		LastPoint=CurrentPoint;
	}
	else if((event->buttons()&Qt::LeftButton)&&GetMode()==MODE_SLICE)
	{
		CurrentPoint = event->pos();
		int yvalue   = LastPoint.y()-CurrentPoint.y();
		int news=this->GetSlice()+yvalue;
		this->SetSlice(news);
		emit s_slicechanged(this->GetSlice());
		LastPoint    = CurrentPoint;
	}
	amyZoomLing::mouseMoveEvent(event);
}
void amyCubeLing::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Equal)
	{
		int news=this->GetSlice()+1;
		this->SetSlice(news);
		emit s_slicechanged(this->GetSlice());
	}
	else if(event->key()==Qt::Key_Minus)
	{
		int news=this->GetSlice()-1;
		this->SetSlice(news);
		emit s_slicechanged(this->GetSlice());
	}
}
