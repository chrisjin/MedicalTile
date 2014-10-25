#include"amyWidgetTable.h"
#include<QGridLayout>
#include<qabstractitemmodel.h>
#include<QItemDelegate>
#include<QHeaderView>
#include<QPushButton>
#include<QTableView>
#include<QAbstractItemModel>
#include<QPainter>
#include<QTableWidget>
class amyHeaderView:public QWidget
{
public:
	amyHeaderView(QWidget* p=0):QWidget(p){m_InnerStr="";}
	void SetText(QString str){m_InnerStr=str;}
	void paintEvent(QPaintEvent *)
	{
		QPainter p(this);
		QStyleOptionHeader header;
		header.text=m_InnerStr;
		header.rect=this->rect();
		style()->drawControl(QStyle::CE_Header,&header,&p);
		style()->drawControl(QStyle::CE_HeaderEmptyArea,&header,&p);
		style()->drawControl(QStyle::CE_HeaderSection,&header,&p);
		style()->drawControl(QStyle::CE_HeaderLabel,&header,&p);
	}
private:
	QString m_InnerStr;
};




amyWidgetTableDelegate::amyWidgetTableDelegate(QObject* p):QItemDelegate(p)
{

}
void amyWidgetTableDelegate::ConnectWidget2ModelUpdate(QWidget* w,const char* signal,const QModelIndex& index)const
{
	m_Wigdet2Index.insert(w,index);
	connect(w,signal,this,SLOT(UpdateModel()));

	//QAbstractItemModel* m=(QAbstractItemModel*)index.model();
	//connect(m,SIGNAL(dataChanged()))
}
void amyWidgetTableDelegate::UpdateModel()
{
	QWidget* w=qobject_cast<QWidget*>(this->sender());
	QModelIndex index=this->m_Wigdet2Index.value(w);
	QAbstractItemModel* m=(QAbstractItemModel*)index.model();
	if(m&&w)
	this->setModelData(w,m,index);
}
void amyWidgetTableDelegate::UpdateView()
{

}

amyWidgetTableArea::amyWidgetTableArea(QWidget* p):QScrollArea(p)
{
	m_Delegate=0;
	m_Model=0;
}
amyWidgetTableArea::~amyWidgetTableArea()
{
	if(m_Delegate)
		delete m_Delegate;
	if(m_Model)
		delete m_Model;
}
void amyWidgetTableArea::SetDelegate(QItemDelegate* d)
{
	this->m_Delegate=d;
	UpdateModelDelegate();
}
void amyWidgetTableArea::SetModel(QAbstractTableModel* m)
{
	this->m_Model=m;
	UpdateModelDelegate();
}
void amyWidgetTableArea::UpdateModelDelegate()
{
	if(m_Model&&m_Delegate)
	{
		//this->setContentsMargins(0,0,0,0);
		//QGridLayout* l=new QGridLayout;
		//l->setContentsMargins(0,0,0,0);
		QTableWidget* test=new QTableWidget(this);
		test->setRowCount(1);
		test->setColumnCount(1);
		test->hide();
		QWidget* centralwidget=new QWidget(this);
		//l->addWidget(new QPushButton("ss",this),0,0);
		//l->addWidget(new QPushButton("ss",this),0,1);
		int baseline=test->horizontalHeader()->height();
		for(int i=0;i<this->m_Model->columnCount();i++)
		{
			amyHeaderView* header=new amyHeaderView(this);
			int h=test->horizontalHeader()->sizeHint().height();
			header->SetText(this->m_Model->headerData(i,Qt::Horizontal).toString());
			header->setGeometry(i*50,0,50,h);
		}
		for(int i=1;i<=this->m_Model->rowCount();i++)
		{
			for(int j=0;j<this->m_Model->columnCount();j++)
			{
				QStyleOptionViewItem o;
				QModelIndex index=this->m_Model->index(i-1,j);
				QWidget *w=this->m_Delegate->createEditor(this,o,index);
				this->m_Delegate->setEditorData(w,index);

				int h=test->verticalHeader()->defaultSectionSize();
				w->setGeometry(j*50,(i-1)*h+baseline,50,h);
			}
		}
		this->setWidget(centralwidget);
	}
}
amyWidgetTableView::amyWidgetTableView(QWidget* p):QWidget(p)
{
	m_Table=new amyWidgetTableArea(this);
	QVBoxLayout* l=new QVBoxLayout(this);
	this->setLayout(l);
	l->setContentsMargins(0,0,0,0);
	l->setSpacing(0);
	this->layout()->addWidget(m_Table);
}
void amyWidgetTableView::SetDelegate(QItemDelegate* d)
{
	m_Table->SetDelegate(d);
}
void amyWidgetTableView::SetModel(QAbstractTableModel* m)
{
	m_Table->SetModel(m);
}