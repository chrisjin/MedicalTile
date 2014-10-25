#include"amyAlgorithmScrollArea.h"
#include"amyAlgorithmManager.h"
#include<QBoxLayout>
#include<QPushButton>
#include"amyAlgorithm.h"
#include<QApplication>
#include<QDesktopWidget>
amyAlgorithmScrollArea::amyAlgorithmScrollArea(QWidget* p):QScrollArea(p)
{
	m_MainWidget=new QWidget(this);
	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	this->setWidget(m_MainWidget);
	l->addWidget(m_MainWidget);
	ensureWidgetVisible(m_MainWidget);
	this->setWidgetResizable(1);
	this->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
}

void amyAlgorithmScrollArea::SetAlgorithmArr(vector<amyAlgorithmQ*>& algoarr)
{
	m_AlgoArr=algoarr;
	QVBoxLayout* ivl=new QVBoxLayout(m_MainWidget);
	amyAlgorithmManager* am=amyAlgorithmManager::GetInstance();
	int width=0;
	for(int j=0;j<algoarr.size();j++)
	{
		QWidget* line=new WidgetForOneAlgorithm(algoarr[j],this);
		ivl->addWidget(line,0,Qt::AlignTop);
	}
	ivl->setSpacing(0);
	ivl->setMargin(0);
	ivl->setContentsMargins(0,0,0,0);
	ivl->addStretch();
	m_MainWidget->setLayout(ivl);

	this->adjustSize();
}


amyAlgorithmButton::amyAlgorithmButton(QWidget* p):QPushButton(p)
{

}

amyAlgorithmButton::amyAlgorithmButton(amyAlgorithmQ* algo,QWidget* p):QPushButton(p)
{
	QString con=algo->GetAlgorithm()->GetAlgorithmName();
	this->setText(con+"\n");
	//this->setFixedHeight(64);
	this->setStyleSheet("Text-align:left");
	m_AlgoIcon=algo->GetAlgorithm()->GetIcon();
	if(m_AlgoIcon==0)
		this->setIcon(QIcon(":/ICON/PluginButton"));
	else
		this->setIcon(*m_AlgoIcon);
	this->setIconSize(QSize(this->height()-2,this->height()-2));
}

WidgetForOneAlgorithm::WidgetForOneAlgorithm(amyAlgorithmQ* algo,QWidget* p):QWidget(p)
{
	m_Algo=algo;
	m_Panel=m_Algo->GetAlgorithm()->CreatePanel(this);
	if(m_Panel)
	{
		m_Panel->setWindowFlags(Qt::Widget|Qt::Popup);
		m_Panel->setFrameStyle(QFrame::WinPanel|QFrame::Raised );
		//m_Panel->resize(150,100);
	}
	
	
	QHBoxLayout* hl=new QHBoxLayout(this);
	hl->setSpacing(0);
	hl->setMargin(0);
	hl->setContentsMargins(0,0,0,0);
	this->setLayout(hl);


	m_ApplyBtn=new amyAlgorithmButton(algo,this);
	hl->addWidget(m_ApplyBtn,4);
	

	m_PanelBtn=new QPushButton(">",this);
	m_PanelBtn->setFixedHeight(m_ApplyBtn->height());
	m_PanelBtn->setFixedWidth(20);
	connect(m_PanelBtn,SIGNAL(clicked()),this,SLOT(ShowPanel()));
	hl->addWidget(m_PanelBtn,1);

	
	amyAlgorithmManager* am=amyAlgorithmManager::GetInstance();
	am->ConnectRetrieveSignal(m_ApplyBtn,SIGNAL(clicked()),algo);
}

void WidgetForOneAlgorithm::ShowPanel()
{
	if(m_Panel)
	{
		QPoint sp=mapToGlobal( m_PanelBtn->geometry().topRight() );
		m_Panel->move( sp );

		QDesktopWidget* dw=QApplication::desktop();
		QRect r=dw->rect();
		QRect pr=m_Panel->geometry();
		if(!r.contains(pr))
		{
			QPoint sbl=dw->rect().bottomLeft();
			QPoint pbl=pr.bottomLeft();

			QPoint stl=dw->rect().topLeft();
			QPoint ptl=pr.topLeft();
			
			
			int dif=0;
			if(pbl.y()>sbl.y())
				dif=sbl.y()-pbl.y();

			if(ptl.y()<stl.y())
				dif=stl.y()-ptl.y();

			sp.ry()+=dif;
			m_Panel->move( sp );
		}

		m_Panel->show();
	}
}