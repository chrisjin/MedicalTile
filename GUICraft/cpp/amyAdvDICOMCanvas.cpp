#include"amyAdvDICOMCanvas.h"
#include"amyMeasureLing.h"
amyAdvDICOMCanvas::amyAdvDICOMCanvas(QWidget *parent):amyDICOMCanvas(parent)
{
	m_AxialViewSelection=new amySelectionLing(this,QRect(0,0,0,0),"Axi");
	connect(m_AxialViewSelection,SIGNAL(s_selected()),this,SLOT(SelectView()));
	m_CoronalViewSelection=new amySelectionLing(this,QRect(0,0,0,0),"Cor");
	connect(m_CoronalViewSelection,SIGNAL(s_selected()),this,SLOT(SelectView()));
	m_SagittalViewSelection=new amySelectionLing(this,QRect(0,0,0,0),"Sag");
	connect(m_SagittalViewSelection,SIGNAL(s_selected()),this,SLOT(SelectView()));
	UpdateViewSelectionLing();
	HideViewSelectionLing();
}

void amyAdvDICOMCanvas::SelectView()
{
	amySelectionLing* p=(amySelectionLing*)this->sender();
	if(p==m_AxialViewSelection)
	{
		m_CoronalViewSelection->SetSelected(0);
		m_SagittalViewSelection->SetSelected(0);
		SetView(amyUtil::AXIAL);
	}
	if(p==m_CoronalViewSelection)
	{
		m_AxialViewSelection->SetSelected(0);
		m_SagittalViewSelection->SetSelected(0);
		SetView(amyUtil::CORONAL);
	}
	if(p==m_SagittalViewSelection)
	{
		m_AxialViewSelection->SetSelected(0);
		m_CoronalViewSelection->SetSelected(0);
		SetView(amyUtil::SAGITTAL);
	}
}


void amyAdvDICOMCanvas::HideViewSelectionLing()
{
	m_AxialViewSelection->Hide();
	m_CoronalViewSelection->Hide();
	m_SagittalViewSelection->Hide();
	repaint();
}
void amyAdvDICOMCanvas::SetViewSelectionLing(amyUtil::ePlane p)
{
	switch(p)
	{
	case amyUtil::AXIAL:
		m_AxialViewSelection->SetSelected(1);
		break;
	case amyUtil::CORONAL:
		m_CoronalViewSelection->SetSelected(1);
		break;
	case amyUtil::SAGITTAL:
		m_SagittalViewSelection->SetSelected(1);
		break;
	}
}
void amyAdvDICOMCanvas::ShowViewSelectionLing()
{
	m_AxialViewSelection->Show();
	m_CoronalViewSelection->Show();
	m_SagittalViewSelection->Show();
	repaint();
}
void amyAdvDICOMCanvas::UpdateViewSelectionLing()
{
	QRect r=this->rect();
	int bo=r.bottom();
	int ri=r.right();
	int spacing=3;
	int eachwidth=64;
	int eachheight=32;
	int cx=ri-eachwidth-spacing;
	int cy=bo-eachheight-spacing;
	m_SagittalViewSelection->SetRect(QRect(cx,cy,eachwidth,eachheight));
	cx-=eachwidth+spacing;
	m_CoronalViewSelection->SetRect(QRect(cx,cy,eachwidth,eachheight));
	cx-=eachwidth+spacing;
	m_AxialViewSelection->SetRect(QRect(cx,cy,eachwidth,eachheight));
}
void amyAdvDICOMCanvas::resizeEvent(QResizeEvent* e)
{
	UpdateViewSelectionLing();
	amyCanvas::resizeEvent(e);
}

bool amyAdvDICOMCanvas::OnAcceptSeries(amyKeeper<amySeries> k)
{
	bool ret = amyDICOMCanvas::OnAcceptSeries(k);
	UpdateViewSelectionLing();
	ShowViewSelectionLing();
	SetViewSelectionLing(this->GetCubeLing()->GetView());
	return ret;
}
bool amyAdvDICOMCanvas::OnAcceptCube(amyKeeper<amyCube> k)
{
	bool ret = amyDICOMCanvas::OnAcceptCube(k);
	UpdateViewSelectionLing();
	ShowViewSelectionLing();
	SetViewSelectionLing(this->GetCubeLing()->GetView());
	return ret;
}