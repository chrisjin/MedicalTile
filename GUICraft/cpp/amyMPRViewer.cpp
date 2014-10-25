#include"amyMPRViewer.h"
#include"amyDICOMCanvas.h"
#include<QHBoxLayout>
#include"amyMeasureLing.h"
#include"amyMPRLineCubeLing.h"
#include"amy3DViewer.h"
amyMPRViewer::amyMPRViewer(QWidget* p):QWidget(p)
{
	m_AxialViewer=new amyDICOMCanvas(this);
	m_CoronalViewer=new amyDICOMCanvas(this);
	m_SagittalViewer=new amyDICOMCanvas(this);
	
	///Sag:blue Axial:red Coronal:green
	m_AxialLing=new amyMPRLineCubeLing();
	m_AxialLing->SetLineColor(Qt::Vertical,Qt::blue);
	m_AxialLing->SetLineColor(Qt::Horizontal,Qt::green);
	m_AxialViewer->ReplaceCubeLing(m_AxialLing);

	m_CoronalLing=new amyMPRLineCubeLing();
	m_CoronalLing->SetLineColor(Qt::Vertical,Qt::blue);
	m_CoronalLing->SetLineColor(Qt::Horizontal,Qt::red);
	m_CoronalViewer->ReplaceCubeLing(m_CoronalLing);
	
	m_SagittalLing=new amyMPRLineCubeLing();
	m_SagittalLing->SetLineColor(Qt::Vertical,Qt::green);
	m_SagittalLing->SetLineColor(Qt::Horizontal,Qt::red);
	m_SagittalViewer->ReplaceCubeLing(m_SagittalLing);

	connect(m_AxialLing,SIGNAL(s_verticalposchanged(int)),this,SLOT(AxialVertical(int)));
	connect(m_AxialLing,SIGNAL(s_horizontalposchanged(int)),this,SLOT(AxialHorizontal(int)));
	connect(m_AxialLing,SIGNAL(s_slicechanged(int)),this,SLOT(AxialSliceChange(int)));

	connect(m_CoronalLing,SIGNAL(s_verticalposchanged(int)),this,SLOT(CoronalVertical(int)));
	connect(m_CoronalLing,SIGNAL(s_horizontalposchanged(int)),this,SLOT(CoronalHorizontal(int)));
	connect(m_CoronalLing,SIGNAL(s_slicechanged(int)),this,SLOT(CoronalSliceChange(int)));

	connect(m_SagittalLing,SIGNAL(s_verticalposchanged(int)),this,SLOT(SagittalVertical(int)));
	connect(m_SagittalLing,SIGNAL(s_horizontalposchanged(int)),this,SLOT(SagittalHorizontal(int)));
	connect(m_SagittalLing,SIGNAL(s_slicechanged(int)),this,SLOT(SagittalSliceChange(int)));
	
	QVBoxLayout* mainlayout=new QVBoxLayout;
	mainlayout->setContentsMargins(0,0,0,0);

	
	//m_3DViewer=new amy3DViewer(this);
	//mainlayout->addWidget(m_3DViewer);

	QHBoxLayout* l=new QHBoxLayout;
	this->setLayout(mainlayout);
	mainlayout->addLayout(l);
	l->addWidget(m_AxialViewer);
	l->addWidget(m_CoronalViewer);
	l->addWidget(m_SagittalViewer);

	
	connect(m_AxialViewer,SIGNAL(s_dropped()),this,SLOT(OnDrop()));
	connect(m_CoronalViewer,SIGNAL(s_dropped()),this,SLOT(OnDrop()));
	connect(m_SagittalViewer,SIGNAL(s_dropped()),this,SLOT(OnDrop()));
}

void amyMPRViewer::OnDrop()
{
	amyDICOMCanvas* s=(amyDICOMCanvas*)this->sender();
	amyCube* k=s->GetCubeLing()->GetInput();
	if(k)
	{
		if(s!=m_AxialViewer)
			m_AxialViewer->GetCubeLing()->SetInput(k);
		if(s!=m_CoronalViewer)
			m_CoronalViewer->GetCubeLing()->SetInput(k);
		if(s!=m_SagittalViewer)
			m_SagittalViewer->GetCubeLing()->SetInput(k);

		m_AxialViewer->SetView(amyUtil::AXIAL);
		int num=m_AxialLing->GetSliceNum();
		m_AxialLing->SetSlice(num/2);
		m_CoronalLing->SetLinePos(Qt::Horizontal,num/2);
		m_SagittalLing->SetLinePos(Qt::Horizontal,num/2);

		m_CoronalViewer->SetView(amyUtil::CORONAL);
		num=m_CoronalLing->GetSliceNum();
		m_CoronalLing->SetSlice(num/2);
		m_AxialLing->SetLinePos(Qt::Horizontal,num/2);
		m_SagittalLing->SetLinePos(Qt::Vertical,num/2);

		m_SagittalViewer->SetView(amyUtil::SAGITTAL);
		num=m_SagittalLing->GetSliceNum();
		m_SagittalLing->SetSlice(num/2);
		m_AxialLing->SetLinePos(Qt::Vertical,num/2);
		m_CoronalLing->SetLinePos(Qt::Vertical,num/2);

		//m_3DViewer->SetInput(k);
	}
}

void amyMPRViewer::AxialHorizontal(int a)//////->Coronal View
{
	int slice=a;
	int slicenum=m_CoronalLing->GetSliceNum();
	if(m_CoronalLing->GetInputView()==amyUtil::CORONAL)
	{
		slice=slicenum-1-a;
	}
	this->m_CoronalViewer->GetCubeLing()->SetSlice(slice);

	this->m_SagittalLing->SetLinePos(Qt::Vertical,a);
	this->m_SagittalViewer->repaint();
}
void amyMPRViewer::AxialVertical(int a)////->Saggital View
{
	this->m_SagittalViewer->GetCubeLing()->SetSlice(a);

	this->m_CoronalLing->SetLinePos(Qt::Vertical,a);
	this->m_CoronalViewer->repaint();
}
void amyMPRViewer::CoronalHorizontal(int a)////->AxialView
{
	int slice=a;
	int slicenum=m_AxialLing->GetSliceNum();
	if(m_AxialLing->GetInputView()==amyUtil::AXIAL)
	{
		slice=slicenum-1-a;
	}
	this->m_AxialViewer->GetCubeLing()->SetSlice(slice);

	m_SagittalLing->SetLinePos(Qt::Horizontal,a);
	this->m_SagittalViewer->repaint();
}
void amyMPRViewer::CoronalVertical(int a)////->Saggital View
{
	this->m_SagittalViewer->GetCubeLing()->SetSlice(a);

	this->m_AxialLing->SetLinePos(Qt::Vertical,a);
	this->m_AxialViewer->repaint();
}
void amyMPRViewer::SagittalHorizontal(int a)////->Axial View
{
	int slice=a;
	int slicenum=m_AxialLing->GetSliceNum();
	if(m_AxialLing->GetInputView()==amyUtil::AXIAL)
	{
		slice=slicenum-1-a;
	}
	this->m_AxialViewer->GetCubeLing()->SetSlice(slice);

	this->m_CoronalLing->SetLinePos(Qt::Horizontal,a);
	this->m_CoronalViewer->repaint();
}
void amyMPRViewer::SagittalVertical(int a)////->Coronal View
{
	int slice=a;
	int slicenum=m_CoronalLing->GetSliceNum();
	if(m_CoronalLing->GetInputView()==amyUtil::CORONAL)
	{
		slice=slicenum-1-a;
	}
	this->m_CoronalViewer->GetCubeLing()->SetSlice(slice);

	this->m_AxialLing->SetLinePos(Qt::Horizontal,a);
	this->m_AxialViewer->repaint();
}
void amyMPRViewer::CoronalSliceChange(int a)
{
	int slice=a;
	int slicenum=m_CoronalLing->GetSliceNum();
	if(m_CoronalLing->GetInputView()==amyUtil::CORONAL)
	{
		slice=slicenum-1-a;
	}
	m_AxialLing->SetLinePos(Qt::Horizontal,slice);
	m_SagittalLing->SetLinePos(Qt::Vertical,slice);
	this->m_AxialViewer->repaint();
	m_SagittalViewer->repaint();

}
void amyMPRViewer::AxialSliceChange(int a)
{
	int slice=a;
	int slicenum=m_AxialLing->GetSliceNum();
	if(m_AxialLing->GetInputView()==amyUtil::AXIAL)
	{
		slice=slicenum-1-a;
	}
	m_CoronalLing->SetLinePos(Qt::Horizontal,slice);
	m_SagittalLing->SetLinePos(Qt::Horizontal,slice);
	m_CoronalViewer->repaint();
	m_SagittalViewer->repaint();
}
void amyMPRViewer::SagittalSliceChange(int a)
{
	m_AxialLing->SetLinePos(Qt::Vertical,a);
	m_CoronalLing->SetLinePos(Qt::Vertical,a);
	m_AxialViewer->repaint();
	m_CoronalViewer->repaint();
}

//void amyMPRViewer::AxialLineChanged(int a)
//{
//	m_CoronalLing->SetLinePos(Qt::Horizontal,a);
//	m_SagittalLing->SetLinePos(Qt::Horizontal,a);
//	m_CoronalViewer->repaint();
//	m_SagittalViewer->repaint();
//
//	int slice=a;
//	int slicenum=m_AxialLing->GetSliceNum();
//	if(m_AxialLing->GetInputView()==amyUtil::AXIAL)
//	{
//		slice=slicenum-1-a;
//	}
//	m_AxialLing->SetSlice(slice);
//
//}
//void amyMPRViewer::CoronalLineChanged(int a)
//{
//}
//void amyMPRViewer::SaggitalLineChanged(int a)
//{
//}