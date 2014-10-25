#pragma once
#include"amyLing.h"
#include"amyPure.h"
#include"itkImage.h"
#include"amyCube.h"
#include"amyZoomLing.h"
#include"amyUtil.h"
#include"itkImageSliceConstIteratorWithIndex.h"
class amyCube;
class amyAnnotationLing;
class GUI_INTERFACE amyCubeLing:public amyZoomLing
{
	Q_OBJECT
public:
	enum eMode
	{
		MODE_ZOOM,
		MODE_SLICE,
		MODE_PAN,
		MODE_WINDOW,
		MODE_NULL
	};
	//enum eView
	//{
	//	VIEW_AXIAL,
	//	VIEW_SAGITTAL,
	//	VIEW_CORONAL,
	//	VIEW_DEFAULT
	//};
	amyCubeLing(amyCanvas* can=0);
	//void Render(QPaintDevice* dev);
	void SetCtrlLock(bool is){m_IsCtrlLock=is;}
	bool IsCtrlLock(){return m_IsCtrlLock;}
	void SetSlice(int s);
	int  GetSlice();
	int  GetSliceNum();
	int  GetSliceWidth();
	int  GetSliceHeight();
	void SetWindow(int c,int w);
	void GetWindow(int &c,int &w){c=this->m_WindowCenter;w=this->m_WindowWidth;}
	void InitInput();
	virtual void InitImage(QImage& image);
	virtual void UpdateImage(QImage& image);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *);
	void keyPressEvent ( QKeyEvent * event );
	eMode GetMode(){return m_Mode;}
	void SetMode(eMode m){m_Mode=m;}

	void                       ComputeSliceSizeFromView();
	typedef itk::ImageSliceConstIteratorWithIndex<amyCube::tCube> ItrType;
	ItrType ComputeIteratorFromView();
	void    AdjustImageDirectionFromView(QImage& img);

private:
	bool   m_IsCtrlLock;
	int    m_Slice;
	int    m_WindowWidth;
	int    m_WindowCenter;
	eMode  m_Mode;

	amyCube::tCube::RegionType  m_InputRegion;
	int   m_DensityMax;
	int   m_DensityMin;
	int   m_SliceWidth;
	int   m_SliceHeight;
	int   m_SliceNum;

signals:
	void s_slicechanged(int);
	void s_slicechanging(int);
	void s_inputchanged();
};