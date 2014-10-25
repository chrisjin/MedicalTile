#pragma once
#include<QScrollArea>
#include<QVariant>
#include<QWidget>
#include<QAbstractTableModel>
#include<QItemDelegate>

class amyWidgetTableDelegate:public QItemDelegate
{
	Q_OBJECT
public:
	amyWidgetTableDelegate(QObject* p=0);
	void ConnectWidget2ModelUpdate(QWidget* w,const char* signal,const QModelIndex& index) const;
signals:
	
public slots:
	void UpdateModel(); 
	void UpdateView();
private:
	mutable QMap<QWidget*,QModelIndex> m_Wigdet2Index;
};

class QItemDelegate;
class QAbstractTableModel;
class QGridLayout;

class amyWidgetTableArea:public QScrollArea
{
	Q_OBJECT
public:
	~amyWidgetTableArea();
	amyWidgetTableArea(QWidget* p=0);
	void SetDelegate(QItemDelegate* d);
	void SetModel(QAbstractTableModel* m);
	void UpdateModelDelegate();
private:
	QItemDelegate* m_Delegate;
	QAbstractTableModel* m_Model;
	QGridLayout*   m_Layout;
};

class amyWidgetTableView:public QWidget
{
	Q_OBJECT
public:
	amyWidgetTableView(QWidget* p=0);
	void SetDelegate(QItemDelegate* d);
	void SetModel(QAbstractTableModel* m);
private:
	amyWidgetTableArea* m_Table;
};