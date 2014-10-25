#pragma once
#include"GuiMacro.h"
#include <QAbstractTableModel >
#include <vector>
#include <QStandardItemModel> 
#include<qitemdelegate>
#include "amyUtil.h"
#include"amyKeeper.h"
#include"amyDICOM.h"
using namespace std;
class amyPatient;
class amySeries;
class QIcon;
class GUI_INTERFACE amyPatientModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	amyPatientModel(amyPatient* pat,QObject *parent=0);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	bool setData(QModelIndex const& idx, QVariant const& value, int role);
	int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	~amyPatientModel();
private:
	amyPatient* m_Patient;
	vector<string>  m_Headers;
	int m_RowCount;
};

class GUI_INTERFACE amySeriesDelegate:public QItemDelegate
{
	Q_OBJECT
public:
	amySeriesDelegate(amyPatient* pat,QObject * parent=0);
	virtual ~ amySeriesDelegate(){}

	void paint(QPainter * painter,
		const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	bool editorEvent(QEvent * event,
		QAbstractItemModel * model,
		const QStyleOptionViewItem & option,
		const QModelIndex & index);
private:
	amyPatient* m_Patient;
};

