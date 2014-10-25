#include"amyAlgorithmPanel.h"
#include"amyAlgorithm.h"
#include<QLabel>
#include<QToolBox>
#include<QBoxLayout>
#include<QTreeWidget>
#include<QLineEdit>
#include<QHeaderView>
#include<QPalette>
amyAlgorithmPanel::amyAlgorithmPanel(amyAlgorithm* a,QWidget* p):QFrame(p)
{
	Initialize(a);
}
amyAlgorithm* amyAlgorithmPanel::GetAlgorithm()
{
	return m_Algo;
}
void amyAlgorithmPanel::Initialize(amyAlgorithm* a)
{
	m_Algo=a;
	setMouseTracking(true);
	this->setLayout(new QVBoxLayout(this));
	//this->layout()->addWidget(m_ToolBox);


	m_TreeWidget=new QTreeWidget(this);
	m_TreeWidget->header()->hide();
	m_TreeWidget->setColumnCount(1);
	//m_TreeWidget->setStyleSheet("background-color:rgb(200,200,200)");
    QPalette p = m_TreeWidget->palette();
    p.setColor(QPalette::Base, QColor(200,200,200));
    m_TreeWidget->setPalette(p);
	this->layout()->addWidget(m_TreeWidget);


	string con;
	string author=a->GetAuthor();
	string hint=a->GetHint();
	string desc=a->GetDescription();

	con+="<b>Author:</b>";
	if(author.size())
		con+=author;
	else
		con+="NEMO";
	con+="<br>";

	con+="<b>Hint:</b>";
	if(hint.size())
		con+=hint;
	else
		con+="NONE";
	con+="<br>";

	con+="<b>Description:</b>";
	if(desc.size())
		con+=desc;
	else
		con+="NONE";
	con+="<br>";

	QLabel* label=new QLabel(con.c_str(),this);
	label->setWordWrap(true);
	label->setOpenExternalLinks(1);
	addPanel(a->GetAlgorithmName(),label);



	//m_ToolBox->addItem(tw,a->GetAlgorithmName());
	m_TreeWidget->expandAll();
	this->adjustSize();
	this->resize(300,400);
}
void amyAlgorithmPanel::addPanel(QString name,QWidget* w)
{

	QTreeWidgetItem *item=new QTreeWidgetItem((QTreeWidget*)0,QStringList(name));
	m_TreeWidget->addTopLevelItem(item);
	m_TreeWidget->expandItem(item);
	{
		QTreeWidgetItem* citem=new QTreeWidgetItem();
		item->addChild(citem);
		m_TreeWidget->setItemWidget(citem,0,w);
	}

}

void amyAlgorithmPanel::focusOutEvent ( QFocusEvent * event )
{
	emit s_focusout();
}

void amyAlgorithmPanel::hideEvent(QHideEvent *)
{
	emit s_focusout();
}