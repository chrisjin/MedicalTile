#include"amyProgressBar.h"
#include<QProgressBar>
#include<QBoxLayout>
IMPLEMENT_SINGLETON(amyProgressBar)
amyProgressBar::amyProgressBar()
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);	
	m_Bar=new QProgressBar(this);

	QHBoxLayout* l=new QHBoxLayout(this);
	this->setLayout(l);
	l->addWidget(m_Bar);
}
void amyProgressBar::SetRange(int a,int b)
{
	m_Bar->setMaximum(a);
	m_Bar->setMaximum(b);
}
void amyProgressBar::SetValue(int c)
{
	m_Bar->setValue(c);
}