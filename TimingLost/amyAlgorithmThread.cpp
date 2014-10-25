#include"amyAlgorithmThread.h"
#include"amyAlgorithm.h"
#include<QDialog>
#include<QLabel>
#include<QBoxLayout>
IMPLEMENT_SINGLETON(DefaultAlgorithmDialog)
DefaultAlgorithmDialog::DefaultAlgorithmDialog()
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);	
	QLabel* l=new QLabel(this);
	l->setText("Runing...");
	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(l);
	this->resize(400,200);
}
amyAlgorithmThread::amyAlgorithmThread()
{
	m_Algo=0;
}
void amyAlgorithmThread::run()
{
	if(m_Algo)
	{
		m_Algo->Run();
	}
}