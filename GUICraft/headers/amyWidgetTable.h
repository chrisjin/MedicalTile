#pragma once
#include<QScrollArea>
#include<QMap>
#include<QModelIndex>
class QAbstractTableModel;
class QItemDelegate;
class QHeaderView;
class QGridLayout;
class amyWidgetTable:public QWidget
{
public:
	amyWidgetTable(QWidget* p);
private:
	QHeaderView*			m_HorizontalHeader;
	QHeaderView*			m_VerticalHeader;
};
class amyWidgetInnerTable:public QScrollArea
{
	Q_OBJECT
public:
	amyWidgetInnerTable(QWidget* p=0);
	void SetDelegate(QItemDelegate* d);
	void SetModel(QAbstractTableModel* m);
	
	
public slots:
	void UpdateView2Model();
	void UpdateModel2Vew();
private:
	QItemDelegate*			m_Delegate;
	QAbstractTableModel*	m_Model;
	QMap<QWidget*,QModelIndex> m_Widget2Index;
	QGridLayout*            m_Layout;
};