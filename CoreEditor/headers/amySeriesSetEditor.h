#pragma once
#include"amyVariableEditor.h"
#include<QTableWidget>
#include"amyKeeper.h"
#include"amyEditorHive.h"
#include<QPixmap>
class amySeries;
class QPaintEvent;
class QLabel;
class amySeriesWidget:public QWidget
{
	Q_OBJECT
public:
	amySeriesWidget(amyKeeper<amySeries> ser,QWidget* p=0);
	~amySeriesWidget();
	amyKeeper<amySeries> GetSeries(){return m_Series;}
	void SetDelete(bool v);
	bool IsDeleted(){return m_IsDeleted;}
	void paintEvent(QPaintEvent*);
private:
	bool m_IsDeleted;
	amyKeeper<amySeries> m_Series;
	QPixmap  m_Thumb;
	QPixmap  m_DeletedThumb;
	QLabel  *m_Label;
};


class amySeriesSetEditor:public amyVariableEditor
{
	Q_OBJECT
public:
	amySeriesSetEditor(QWidget *parent=0);
	~amySeriesSetEditor(){}
	void InitInput();
	bool eventFilter(QObject *obj, QEvent *event);
	void contextTableMenuEvent(QContextMenuEvent *);
	void Confirm();
public slots:
	void DeleteTableCell();
	void RecoverTableCell();
	void AfterConfirm();
private:
	QTableWidget* m_Table;
};


class amySeriesSetEditorHive:public amyEditorHive
{
public:
	amyVariableEditor* Produce(){return new amySeriesSetEditor;}
	const char*        GetName(){return "Series Viewer";}
	virtual bool               CheckInputNum(int num)
	{
		if(num==1)
			return 1;
		else return 0;
	}
	virtual bool			   CheckInputArgument(int index,amyVariable v)
	{
		if(v.GetType()==VTYPE_SERIES_SET)
			return 1;
		else
			return 0;
	};
	QIcon   GetIcon()
	{
		return QIcon(":/ICON/CubeViewer");
	}
};