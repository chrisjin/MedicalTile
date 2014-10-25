#include"amyWidgetTable.h"
#include<QModelIndex>
#include<QHeaderView>
#include<QGridLayout>
#include<QAbstractTableModel>
#include<QItemDelegate>
amyWidgetTable::amyWidgetTable(QWidget* p):QWidget(p)
{
	this->m_HorizontalHeader=new QHeaderView(Qt::Horizontal,this);
	this->m_VerticalHeader=new QHeaderView(Qt::Vertical,this);
}
amyWidgetInnerTable::amyWidgetInnerTable(QWidget* p):QScrollArea(p)
{
	m_Layout=new QGridLayout(this);
	this->setLayout(m_Layout);
}
void amyWidgetInnerTable::SetDelegate(QItemDelegate* d)
{
	this->m_Delegate=d;
}
void amyWidgetInnerTable::SetModel(QAbstractTableModel* m)
{
	this->m_Model=m;
	int c=this->m_Model->columnCount();
	int r=this->m_Model->rowCount();
	for(int i=0;i<c;i++)
		for(int j=0;j<r;j++)
		{
			QStyleOptionViewItem o;
			QModelIndex index=this->m_Model->index(j,i);
			m_Layout->addWidget(this->m_Delegate->createEditor(this,o,index),j,i);
		}
}

void amyWidgetInnerTable::UpdateModel2Vew()
{

}
void amyWidgetInnerTable::UpdateView2Model()
{
	QWidget* w=qobject_cast<QWidget*>(this->sender());
	QMap<QWidget*,QModelIndex>::Iterator itr=this->m_Widget2Index.find(w);
	if(itr==m_Widget2Index.end())
		return;
	else
	{
		QModelIndex indextoupdate=itr.value();
		this->m_Delegate->setModelData(w,this->m_Model,indextoupdate);
	}
}