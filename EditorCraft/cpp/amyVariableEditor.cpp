#include "amyVariableEditor.h"
#include<QHBOXLayout>
#include<QTableWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include"amyVariableManager.h"
amyVariableEditor::amyVariableEditor(QWidget *parent)
	: QDialog(parent)
{
	setAttribute (Qt::WA_DeleteOnClose);
	m_Layout=new QVBoxLayout(this);
	QHBoxLayout* l=new QHBoxLayout(this);
	m_Layout->addLayout(l);

	QLabel* label=new QLabel("Name: ",this);
	label->setStyleSheet("color:white");
	l->addWidget(label);
	m_NameEdit=new QLineEdit;
	l->addWidget(m_NameEdit);

	QPushButton* btc=new QPushButton("Confirm",this);
	connect(btc,SIGNAL(clicked()),this,SLOT(SlotConfirm()));
	l->addWidget(btc);

	QPushButton* btcc=new QPushButton("Cancel",this);
	connect(btcc,SIGNAL(clicked()),this,SLOT(SlotCancel()));
	l->addWidget(btcc);

	m_Widget=new QWidget(this);
	m_Layout->addWidget(m_Widget);
	
	QPalette p;
	this->setAutoFillBackground(true);
	p = this->palette();
	p.setColor(QPalette::Window,QColor(47,65,95));
	this->setPalette(p);

	m_Widget->setAutoFillBackground(true);
	p = m_Widget->palette();
	p.setColor(QPalette::Window,QColor(156,170,193));
	m_Widget->setPalette(p);
}
void amyVariableEditor::InitInput()
{
	amyVariableManager* tm= amyVariableManager::GetInstance();
	m_NameEdit->setText(this->GetInput().GetName().c_str());
	this->setWindowTitle(QString("Name:")+this->GetInput().GetName().c_str()
		+" "+QString("Type:")+tm->GetTypeString(this->GetInput().GetType()).c_str());
}
void amyVariableEditor::SlotConfirm()
{
	Confirm();
	accept();
}
void amyVariableEditor::SlotCancel()
{
	Cancel();
	reject();
}
void amyVariableEditor::Confirm()
{
	QByteArray ba = m_NameEdit->text().toLatin1();
	this->GetInput().SetName(ba.data());
}
void amyVariableEditor::Cancel()
{
}
amyVariableEditor::~amyVariableEditor()
{

}

void	amyVariableEditor::closeEvent( QCloseEvent * event )
{
	//emit s_close();
}

void amyVariableEditor::SetInput(amyVariable v)
{
	this->m_InputArr.clear();
	this->m_InputArr.push_back(v);
	InitInput();
}
amyVariable amyVariableEditor::GetInput()
{
	amyVariable v;
	if(m_InputArr.size()>0)
		v=m_InputArr[0];
	return v;
}
vector<amyVariable>& amyVariableEditor::GetInputArr()
{
	return m_InputArr;
}
void amyVariableEditor::SetInputArr(vector<amyVariable>& varr)
{
	m_InputArr=varr;
	InitInput();
}
//bool amyVariableEditor::CheckInputArgument(int index,amyVariable v)
//{
//	return 1;
//}
//QImage amyVariableEditor::GetIcon()
//{
//	return QImage();
//}
