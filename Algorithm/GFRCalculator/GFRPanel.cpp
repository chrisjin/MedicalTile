#include"GFRPanel.h"
#include<QLabel>
#include"amyscanf.h"
#include"amyFormatEdit.h"
#include<QMessageBox>
GFRPanel::GFRPanel(amyAlgorithm* a,QWidget* p):amyAlgorithmPanel(a,p)
{
	HCT=0.35;
	T1=6;
	T2=15;
	m_Edit=new amyFormatEdit(this);
	m_Edit->scanf("hct:%f;\nT1:%d;T2:%d",&HCT,&T1,&T2);
	this->addPanel("Argument",m_Edit);
	connect(this,SIGNAL(s_focusout()),this,SLOT(Update()));

}

void GFRPanel::Update()
{
	m_Edit->Update();
}