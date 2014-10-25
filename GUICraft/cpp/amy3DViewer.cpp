//#include"amy3DViewer.h"
//#include"mitkView.h"
//#include"mitkImageModel.h"
//#include"mitkVolume.h"
//#include"mitkICVolume.h"
//#include"amyCube.h"
//#include"itkImageRegionConstIterator.h"
//#include"mitkVolumeModel.h"
//#include"mitkOoCVolumeRendererTexture3D.h"
//#include"mitkVolumeProperty.h"
//#include"mitkOoCVolumeRendererRayCasting.h"
//#include"mitkImageScene.h"
//#include"mitkSceneContainer.h"
////#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
////#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)
////#include"vtkRenderer.h"
////#include"vtkWin32OpenGLRenderWindow.h"
////#include"vtkWin32RenderWindowInteractor.h"
////#include"vtkActor2D.h"
////#include"vtkTextMapper.h"
////#include"vtkTextProperty.h"
//amy3DViewer::amy3DViewer(QWidget* p):QWidget(p)
//{
//	//mitkSceneContainer* sc=new mitkSceneContainer;
//	m_ImageScene = new mitkImageScene;
//    //Set the parent window, and fill out the whole parent window
//	//m_ImageScene->SetParent(this->winId());  
// //   m_ImageScene->SetLeft(0);
// //   m_ImageScene->SetTop(0);
// //   m_ImageScene->SetWidth(parentWindowWidth);
// //   m_ImageScene->SetHeight(parentWindowHeight);  
// //   m_ImageScene->Show();
//	m_View = new mitkView;
//	m_ImageScene->SetContainer(m_View);
//
//	
//	//m_View->
//	//m_View->EnableLoD();
//	m_View->SetParent(this->winId());
//	//m_View->SetBackColor(255,255,255);
//	m_View->Show();
//
//	//m_ImageModel = new mitkVolumeModel;
//	//mitkOoCVolumeRendererTexture3D   *ren = new mitkOoCVolumeRendererTexture3D  ;
//	//ren->SetSubVolumeSize(128,128,128);
//	//m_ImageModel->SetRenderer(ren);
//	//
//	//m_View->Update();
//	//mitkVolumeProperty *prop = m_ImageModel->GetProperty();
//
//	//// 设置光源参数
//	//prop->SetAmbient(0.2f);
//	//prop->SetDiffuse(0.8f);
//	//prop->SetSpecular(0.2f);
//	//prop->SetSpecularPower(5.0f);
//
//	//mitkTransferFunction1D *sof = prop->GetScalarOpacity();
//	////	sof->SetMax(255, 1.0f);
//	////	sof->AddPoint(75, 0.0f);
//	////	sof->AddPoint(174, 0.0147059f);
//	////	sof->AddPoint(223, 0.323529f);
//	//int maxVal = 255;
//	//int p3 = (int) (maxVal * 0.3997f + 0.5f);
//	//sof->SetMax(maxVal, 1.0f);
//	//sof->AddPoint(p3, 0.1f);
//	//sof->AddPoint(p3+1, 1.0f);
//
//	//mitkColorTransferFunction *scf = prop->GetScalarColor();
//	////	scf->SetMax(255, 1.0f, 0.0f, 0.0f);
//	//// 	scf->AddPoint(  0, 0.0f, 0.0f, 1.0f);
//	//// 	scf->AddPoint( 63, 0.0f, 1.0f, 1.0f);
//	//// 	scf->AddPoint(127, 0.0f, 1.0f, 0.0f);
//	//// 	scf->AddPoint(191, 1.0f, 1.0f, 0.0f);	
//
//	//scf->SetMax(maxVal, 1.0f, 1.0f, 1.0f);
//	//int p1 = (int) (maxVal * 0.0415f + 0.5f);
//	//int p2 = (int) (maxVal * 0.2657f + 0.5f);
//	//scf->AddPoint(p1, 0.9f, 0.8f, 0.1f);
//	//scf->AddPoint(p2, 0.9f, 0.1f, 0.1f);
//	//scf->AddPoint(p3, 1.0f, 1.0f, 1.0f);
//
//
//	//m_View->AddModel(m_ImageModel);	
//
//	//m_View->EnableLoD();
//	//m_View->Update();
//	//aView->SetParent(this->winId());
//	//
//	//aView->Show();
//	//aView->SetLeft(0);
//	//aView->SetTop(0);
//	//aView->SetWidth(this->rect().width());
//	//aView->SetHeight(this->rect().height());
//	//this->m_Renderer = vtkRenderer::New();
//	////this->m_Renderer->SetBackground(0.3, 0.5, 0.1);
//	//this->m_RenderWindow = vtkWin32OpenGLRenderWindow::New();
//	//this->m_RenderWindow->AddRenderer(this->m_Renderer);
//	//this->m_Interactor = vtkWin32RenderWindowInteractor::New();
//
//	//vtkActor2D *actor2d = vtkActor2D::New();
//	//vtkTextMapper *txt = vtkTextMapper::New();
//	//actor2d->SetMapper(txt);
//	//txt->SetInput("Hello World");
//	//txt->GetTextProperty()->SetFontSize(24);
//	//this->m_Renderer->AddActor2D(actor2d);
//	//txt->Delete();
//	//actor2d->Delete();
//
//	//if (! this->m_Interactor->GetInitialized()) 
//	//{
//	//	this->m_RenderWindow->SetWindowId(this->winId());
//	//	this->m_RenderWindow->WindowInitialize();
//	//	this->m_Interactor->SetRenderWindow(this->m_RenderWindow);
//	//	this->m_Interactor->Initialize();
//	//}
//}
//amy3DViewer::~amy3DViewer()
//{
//	m_View->Delete();
//}
//mitkVolume* ConvertI2M(amyCube* cube)
//{
//	amyCube::tCube::SizeType size=cube->obj->GetLargestPossibleRegion().GetSize();
//	amyCube::tCube::SpacingType sp=cube->obj->GetSpacing();
//	mitkVolume* volume=new mitkICVolume;
//	volume->SetWidth(size[0]);
//	volume->SetHeight(size[1]);
//	volume->SetSliceNum(size[2]);
//	volume->SetSpacingX(sp[0]);
//	volume->SetSpacingY(sp[1]);
//	volume->SetSpacingZ(sp[2]);
//	volume->SetChannelNum(1);
//	volume->SetDataTypeToShort();
//	//volume->AddReference();
//	typedef itk::ImageRegionConstIterator<amyCube::tCube> ItrType;
//	ItrType itr(cube->obj,cube->obj->GetLargestPossibleRegion());
//	if(volume->Allocate())
//	{
//		short* v=(short*)volume->GetData();
//		itr.GoToBegin();
//		for(int i=0;!itr.IsAtEnd();++itr,++i)
//		{
//			*(v+i)=itr.Get();
//		}
//	}
//	return volume;
//}
//void amy3DViewer::SetInput(amyCube* cube)
//{
//	mitkVolume* v=ConvertI2M(cube);
//	m_ImageModel->SetData(v);
//	//m_ImageModel->SetViewMode(mitkImageModel::VIEW_XY);
// //   m_ImageModel->SetCurrentSliceNumber(0); 
//	//m_View->AddModel(m_ImageModel);
//	m_View->Update();
//}
//void amy3DViewer::resizeEvent(QResizeEvent* e)
//{
//	//if(!m_View->GetParent())
//	//{
//	//	m_View->SetParent(this->winId());
//	//	m_View->Show();
//	//}
//	m_View->SetLeft(0);
//	m_View->SetTop(0);
//	m_View->SetWidth(this->rect().width());
//	m_View->SetHeight(this->rect().height());
//	//m_View->set
//}
////void amy3DViewer::paintEvent(QPaintEvent *e)
////{
////	//this->m_RenderWindow->Render();
////	//if(!m_View->GetParent())
////	//{
////
////	//}
////	
////}
