#include"amyscanf.h"
#include<qstring>
#include<vector>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QTableWidget>
#include<QApplication>
using namespace std;
namespace amyUtil
{

ScanfPatternDialog::ScanfPatternDialog(const char* str,QWidget *parent):QDialog(parent)
{
	//moveToThread(QApplication::instance()->thread());
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);	
	vector<QString> strfrag;
	QString currentstr="";
	QVBoxLayout* l=new QVBoxLayout(this);
	
	this->setLayout(l);
	QHBoxLayout* currentline=new QHBoxLayout(this);
	l->addLayout(currentline);
	int i=0;
	while(1)
	{
		char c=str[i];
		if(c==0)
		{
			if(currentstr.size()!=0)
			{
				strfrag.push_back(currentstr);
				QLabel* label=new QLabel(currentstr,this);
				currentline->addWidget(label);
			}
			break;
		}
		if(c!='%'&&c!='\n')
		{
			currentstr+=c;
			i++;
		}
		else if(c=='\n')
		{
			if(currentstr.size()>0)
			{
				QLabel* label=new QLabel(currentstr,this);
				currentline->addWidget(label);
				currentstr="";
			}
			currentline=new QHBoxLayout(this);
			l->addLayout(currentline);
			i++;
		}
		else if(c=='%')
		{
			strfrag.push_back(currentstr);
			argtype.push_back(str[i+1]);
			i+=2;
			QLabel* label=new QLabel(currentstr,this);
			currentline->addWidget(label);

			QLineEdit* edit=new QLineEdit(this);
			currentline->addWidget(edit);
			m_EditArr.push_back(edit);

			currentstr="";
		}
	}
	currentline=new QHBoxLayout(this);
	l->addLayout(currentline);
	QPushButton* b=new QPushButton(QString::fromLocal8Bit("确定"),this);
	currentline->addWidget(b);
	connect(b,SIGNAL(clicked()),this,SLOT(accept()));
	connect(b,SIGNAL(clicked()),this,SLOT(OnOk()));

}
void ScanfPatternDialog::OnOk()
{
	int argnum=m_EditArr.size();
	for(int i=0;i<argnum;i++)
	{
		switch(argtype[i])
		{
		case 'd':
			{
				*((int*)acceptpointer[i])=m_EditArr[i]->text().toInt();
			}
			break;
		case 'f':
			{
				*((float*)acceptpointer[i])=m_EditArr[i]->text().toFloat();
			}
			break;
		case 's':
			{
				strcpy((char*)acceptpointer[i],m_EditArr[i]->text().toLocal8Bit().data());
			}
		}
	}
}
QWidget* scanfpanel(QWidget* p,const char* fmt,...)
{
	return 0;
}
void scanf(const char* fmt,...)
{
	ScanfPatternDialog d(fmt);
	int argnum=d.m_EditArr.size();

	va_list arg_ptr; 
    va_start(arg_ptr, fmt); 
    for(int i = 0; i < argnum; i++)
    {
		switch(d.argtype[i])
		{
		case 'd':
			{
				int* value = va_arg(arg_ptr,int*);
				d.m_EditArr[i]->setText(QString::number(*value));
				d.acceptpointer.push_back(value);
				break;
			}
		case 'f':
			{
				float* value = va_arg(arg_ptr,float*);
				d.m_EditArr[i]->setText(QString::number(*value));
				d.acceptpointer.push_back(value);
				break;
			}
		case 's':
			{
				char* value = va_arg(arg_ptr,char*);
				if(strlen(value)!=0)
					d.m_EditArr[i]->setText(QString(value));
				d.acceptpointer.push_back(value);
				break;
			}

		}
    }
    va_end(arg_ptr);

	d.exec();
}

void scanf(const char* prumpt,vector<float>& arr)
{
	ScanfArrDialog d(prumpt,arr);
	d.exec();
}

ScanfArrDialog::ScanfArrDialog(const char* prumpt,vector<float>& arr,QWidget *parent):QDialog(parent),m_Arr(arr)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	this->resize(800,100);
	m_Arr=arr;

	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	QLabel* label=new QLabel(prumpt,this);
	l->addWidget(label);


	m_Table=new QTableWidget(this);
	m_Table->setRowCount(1);
	m_Table->setColumnCount(arr.size());
	for(int i=0;i<arr.size();i++)
	{
		QTableWidgetItem* item=new QTableWidgetItem(QString::number(arr[i]));
		m_Table->setItem(0,i,item);
	}
	l->addWidget(m_Table);
	QPushButton* b=new QPushButton(QString::fromLocal8Bit("确定"),this);
	l->addWidget(b);
	connect(b,SIGNAL(clicked()),this,SLOT(accept()));
	connect(b,SIGNAL(clicked()),this,SLOT(OnOk()));
}

void ScanfArrDialog::OnOk()
{
	for(int i=0;i<m_Table->columnCount();i++)
	{
		QByteArray ba = m_Table->item(0,i)->text().toLatin1();
		m_Arr[i]=atof(ba.data());
	}
}
}//namespace