#include "ROIDialog.h"
#include<QHBoxLayout>
#include"amyROILing.h"
#include<QPushButton>
ROIDialog::ROIDialog(QWidget *parent)
	: QDialog(parent)
{
	this->resize(512,512);
	QVBoxLayout* vl=new QVBoxLayout(this);
	setLayout(vl);

	amyCanvas* c=new amyCanvas(this);
	m_Ling=new amyROILing(c);
	m_Ling->SetInput(0);
	m_Ling->SetCtrlLock(1);
	this->layout()->addWidget(c);

	QHBoxLayout* l=new QHBoxLayout(this);
	vl->addLayout(l);

	QPushButton* ok=new QPushButton("OK",this);
	l->addWidget(ok);
	connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
	QPushButton* cancel=new QPushButton("Cancel",this);
	l->addWidget(cancel);
	connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
}

ROIDialog::~ROIDialog()
{

}
QRect ROIDialog::GetRect()
{
	return m_Ling->GetRect();
}
void ROIDialog::InitInput()
{
	amyCube* c=this->GetInput();
	if(!c)
		return;
	m_Ling->SetInput(c);
}
