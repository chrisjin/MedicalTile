#pragma once
#include"CoreEditorMacro.h"
#include"amyVariableEditor.h"
#include"amyEditorHive.h"
#include<QItemDelegate>
#include"amyWidgetTable.h"
class amyWidgetTableView;
class amyDataWidget;
class QTableWidget;
class amyFloatArr;
class QPaintEvent;
class QKeyEvent;
class QTableView;
class amyArray;
class QComboBox;
class QSpinBox;
class DataModel;
class DataRoleTableModel:public QAbstractTableModel
{
	Q_OBJECT
public:
	enum Axis{X,Y,NONE};
	DataRoleTableModel(amyKeeper<DataModel> innermodel,QObject *parent = 0);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	bool setData(QModelIndex const& idx, QVariant const& value, int role);
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags	flags ( const QModelIndex & index ) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
private:
	mutable amyKeeper<DataModel> m_DataModel;
};
class DataRoleTableDelegate:public amyWidgetTableDelegate
{
	Q_OBJECT
public:
	DataRoleTableDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void paint(QPainter *painter,  
                          const QStyleOptionViewItem &option,  
                          const QModelIndex &index) const;  
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
	mutable amyKeeper<DataModel> m_DataModel;
};

class amyDoubleThresholdWidget;
class COREEDITOR_INTERFACE amyDataEditor:public amyVariableEditor
{
	Q_OBJECT
public:
	amyDataEditor(QWidget *parent=0);
	void InitInput(); 
	void Confirm();
	void keyTablePressEvent( QKeyEvent * event);
	bool eventFilter(QObject *target, QEvent *event);
	void Copy();
public slots:
	void UpdateBarRange();
private:
	amyDoubleThresholdWidget *m_HorizontalBar;
	amyDoubleThresholdWidget *m_VerticalBar;
	QTableWidget* m_Table;
	amyWidgetTableView*   m_RoleTableView;
	amyDataWidget* m_DrawCurveWidget;
	amyKeeper<DataModel> m_DataModel;
};

class amyDataEditorHive:public amyEditorHive
{
public:
	amyVariableEditor* Produce(){return new amyDataEditor;}
	const char*        GetName(){return "Data Viewer";}
	virtual bool               CheckInputNum(int num)
	{
		return 1;
	}
	virtual bool			   CheckInputArgument(int index,amyVariable v)
	{
		if(v.GetType()==VTYPE_DATA_ARRAY||v.GetType()==VTYPE_DATA_MATRIX)
			return 1;
		else
			return 0;
	};
	QIcon   GetIcon()
	{
		return QIcon(":/ICON/DataViewer");
	}
};