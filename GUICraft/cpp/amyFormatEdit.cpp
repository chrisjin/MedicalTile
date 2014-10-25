#include"amyFormatEdit.h"
#include<QLineEdit>
#include<QBoxLayout>
#include<QLabel>
amyFormatEdit::amyFormatEdit(QWidget* p):QFrame(p)
{

}
void amyFormatEdit::scanf(const char* fmt,...)
{
	const char* str=fmt;
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

	int argnum=m_EditArr.size();

	va_list arg_ptr; 
	va_start(arg_ptr, fmt); 
	for(int i = 0; i < argnum; i++)
	{
		switch(argtype[i])
		{
		case 'd':
			{
				int* value = va_arg(arg_ptr,int*);
				m_EditArr[i]->setText(QString::number(*value));
				acceptpointer.push_back(value);
				break;
			}
		case 'f':
			{
				float* value = va_arg(arg_ptr,float*);
				m_EditArr[i]->setText(QString::number(*value));
				acceptpointer.push_back(value);
				break;
			}
		case 's':
			{
				char* value = va_arg(arg_ptr,char*);
				if(strlen(value)!=0)
					m_EditArr[i]->setText(QString(value));
				acceptpointer.push_back(value);
				break;
			}

		}
	}
	va_end(arg_ptr);
}

void amyFormatEdit::Update()
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