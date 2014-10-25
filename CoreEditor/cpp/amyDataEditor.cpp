#include"amyDataEditor.h"
#include"amyArray.h"
#include"amyMatrix.h"
#include<QTableWidget>
#include<QVBoxLayout>
#include<QComboBox>
#include<QSpinBox>
#include<QAction>
#include<QPainter>
#include<QApplication>
#include<QHeaderView>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include"amyDataWidget.h"
#include<QSplitter>
#include<QKeyEvent>
#include<QApplication>
#include<QClipBoard>
#include"amyWidgetTable.h"
#include<QPushButton>
#include"amyDoubleThresholdWidget.h"
#include"amyColorButton.h"
amyDataEditor::amyDataEditor(QWidget *parent)
{
	QVBoxLayout* l=new QVBoxLayout(this);
	QWidget* w=this->GetMainWidget();
	w->setLayout(l);

	QSplitter* sptotal=new QSplitter(Qt::Vertical,this);
	l->addWidget(sptotal);

	QSplitter* sptop=new QSplitter(Qt::Horizontal,this);

	m_Table=new QTableWidget(this);
	m_Table->installEventFilter(this);
	QHBoxLayout* testhl=new QHBoxLayout();
	sptop->addWidget(m_Table);


	m_RoleTableView=new amyWidgetTableView(this);
	m_RoleTableView->SetDelegate(new DataRoleTableDelegate(this));
	m_RoleTableView->setFixedWidth(150);
	sptop->addWidget(m_RoleTableView);

	
	sptotal->addWidget(sptop);

	
	QFrame* CanvasWidget=new QFrame(this);
	CanvasWidget->setMinimumHeight(400);
	QGridLayout* gl=new QGridLayout(this);
	gl->setSpacing(0);
	gl->setContentsMargins(0,0,0,0);
	int Span=7;
	m_HorizontalBar=new amyDoubleThresholdWidget(Qt::Horizontal,this);
	m_HorizontalBar->SetBound(0,100);
	m_HorizontalBar->SetThreshold(30,40);
	m_HorizontalBar->setMaximumHeight(40);
	gl->addWidget(m_HorizontalBar,0,0,1,Span);

	QWidget* dummy=new QWidget(this);
	gl->addWidget(dummy,0,Span,1,1);

	m_DrawCurveWidget=new amyDataWidget(this);
	gl->addWidget(m_DrawCurveWidget,1,0,Span,Span);

	
	m_VerticalBar=new amyDoubleThresholdWidget(Qt::Vertical,this);
	m_VerticalBar->SetBound(0,100);
	m_VerticalBar->SetThreshold(30,40);
	m_VerticalBar->setMaximumWidth(40);
	gl->addWidget(m_VerticalBar,1,Span,Span,1);

	CanvasWidget->setLayout(gl);
	connect(m_HorizontalBar,SIGNAL(s_thresholdchanging(float,float)),m_DrawCurveWidget,SLOT(XThresholdChanging(float,float)));
	connect(m_HorizontalBar,SIGNAL(s_thresholdchanged(float,float)),m_DrawCurveWidget,SLOT(XThresholdChanged(float,float)));

	connect(m_VerticalBar,SIGNAL(s_thresholdchanging(float,float)),m_DrawCurveWidget,SLOT(YThresholdChanging(float,float)));
	connect(m_VerticalBar,SIGNAL(s_thresholdchanged(float,float)),m_DrawCurveWidget,SLOT(YThresholdChanged(float,float)));
	
	connect(m_DrawCurveWidget,SIGNAL(s_xyrangechanged()),this,SLOT(UpdateBarRange()));
	sptotal->addWidget(CanvasWidget);

	sptop->setStretchFactor(0,1);
	sptop->setStretchFactor(1,1);
	sptotal->setStretchFactor(0,1);
	sptotal->setStretchFactor(1,3);
	m_DataModel=new DataModel;
	this->resize(800,600);
}
void amyDataEditor::InitInput()
{
	m_DataModel->totaldata.clear();
	vector<amyVariable>& vararr=this->GetInputArr();
	for(int i=0;i<vararr.size();i++)
	{
		if(vararr[i].GetType()==VTYPE_DATA_ARRAY)
		{
			m_DataModel->totaldata.push_back(vararr[i].Get<amyArray>());
		}
		if(vararr[i].GetType()==VTYPE_DATA_MATRIX)
		{
			FETCH(amyMatrix,mat,vararr[i]);
			amyMatrix::tData d=mat();
			for(int j=0;j<d.size();j++)
			{
				m_DataModel->totaldata.push_back(d[j]);
			}
		}
	}
	for(int i=0;i<m_DataModel->totaldata.size();i++)
	{
		if(i==0&&m_DataModel->totaldata.size()!=1)
			m_DataModel->axisrole.push_back(DataModel::X);
		else
			m_DataModel->axisrole.push_back(DataModel::Y);
		m_DataModel->pairrole.push_back(0);
		Qt::GlobalColor gc=Qt::GlobalColor(i%12+7);
		QColor cc=gc;
		m_DataModel->colorrole.push_back(cc);
	}



	m_RoleTableView->SetModel(new DataRoleTableModel(m_DataModel,this));
	m_DrawCurveWidget->SetModel(m_DataModel);
	int col=-1;
	for(int i=0;i<m_DataModel->totaldata.size();i++)
	{
		if(col<m_DataModel->totaldata[i]->size())
		{
			col=m_DataModel->totaldata[i]->size();
		}
	}
	m_Table->setRowCount(m_DataModel->totaldata.size());
	m_Table->setColumnCount(col);
	for(int i=0;i<m_DataModel->totaldata.size();i++)
	{
		amyKeeper<amyArray> kline=m_DataModel->totaldata[i];
		for(int j=0;j<kline->size();j++)
		{
			QTableWidgetItem* item=new QTableWidgetItem(QString::number(kline->at(j)));
			m_Table->setItem(i,j,item);
		}
	}
	int _h=m_Table->verticalHeader()->length()+60;
	int h=_h>250?250:_h;
	m_Table->setMinimumHeight(h);




	amyVariableEditor::InitInput();
}
void amyDataEditor::UpdateBarRange()
{
	float xmax,ymax,xmin,ymin;
	m_DrawCurveWidget->GetXYRange(xmin,xmax,ymin,ymax);
	this->m_HorizontalBar->SetBound(xmin,xmax);
	this->m_HorizontalBar->SetThreshold(xmin,xmax);
	this->m_VerticalBar->SetBound(ymin,ymax);
	this->m_VerticalBar->SetThreshold(ymin,ymax);
	this->m_HorizontalBar->repaint();
	this->m_VerticalBar->repaint();
}
void amyDataEditor::Confirm()
{
	int row=0;
	amyMatrix::tData& dataarr=m_DataModel->totaldata;
	for(int i=0;i<dataarr.size();i++)
	{
		for(int j=0;j<dataarr[i]->size();j++)
		{
			QByteArray ba = m_Table->item(i,j)->text().toLatin1();
			dataarr[i]->at(j)=atof(ba.data());
		}
	}
	amyVariableEditor::Confirm();
}
DataRoleTableModel::DataRoleTableModel(amyKeeper<DataModel> innermodel,QObject *parent):QAbstractTableModel(parent)
{
	m_DataModel=innermodel;
}
Qt::ItemFlags	DataRoleTableModel::flags ( const QModelIndex & index ) const
{
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
int DataRoleTableModel::rowCount(const QModelIndex &parent) const
{
	return m_DataModel->totaldata.size();
}
int	DataRoleTableModel::columnCount ( const QModelIndex & parent ) const
{
	return 3;
}
QVariant DataRoleTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	else if (role == Qt::DisplayRole&&index.column()==0)
	{
		if(index.row()<m_DataModel->axisrole.size())
			return QVariant::fromValue((int)m_DataModel->axisrole[index.row()]);
	}
	else if(role == Qt::DisplayRole&&index.column()==1)
	{
		if(index.row()<m_DataModel->pairrole.size())
			return QVariant::fromValue((int)m_DataModel->pairrole[index.row()]);
	}
	else if(role == Qt::DisplayRole&&index.column()==2)
	{
		if(index.row()<m_DataModel->colorrole.size())
			return m_DataModel->colorrole[index.row()];
	}
	return QVariant();
}
QVariant DataRoleTableModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal)
	{
		if(section==0)
			return "Axis";
		else if(section==1)
			return "Group";
		else if(section==2)
			return "Color";
	}
	else
	{
		return QString("%1").arg(section+1);
	}
}
bool DataRoleTableModel::setData(QModelIndex const& idx, QVariant const& value, int role)
{
	if (Qt::EditRole == role)
	{
		// Update data...

		if(idx.column()==0)
		{
			if(idx.row()<m_DataModel->axisrole.size())
			{
				m_DataModel->axisrole[idx.row()]=(DataModel::Axis)value.toInt();
			}
		}
		else if(idx.column()==1)
		{
			if(idx.row()<m_DataModel->pairrole.size())
			{
				m_DataModel->pairrole[idx.row()]=value.toInt();
			}
		}
		else if(idx.column()==2)
		{
			if(idx.row()<m_DataModel->colorrole.size())
			{
				m_DataModel->colorrole[idx.row()]=value.value<QColor>();
			}
		}
		QModelIndex topLeft = index(0, 0);
		QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);
		m_DataModel->Notify();
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();

		return true;
	}
	return false;
}
DataRoleTableDelegate::DataRoleTableDelegate(QObject *parent):amyWidgetTableDelegate(parent)
{

}

QWidget *DataRoleTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	
	if(index.column()==0)
	{
		QComboBox* cb=new QComboBox(parent);
		cb->addItem("X");
		cb->addItem("Y");
		cb->addItem("NONE");
		this->ConnectWidget2ModelUpdate(cb,SIGNAL(currentIndexChanged(int)),index);
		return cb;
	}
	else if(index.column()==1)
	{
		QComboBox* cb=new QComboBox(parent);
		for(int i=0;i<10;i++)
		{
			cb->addItem(QString::number(i));
		}
		this->ConnectWidget2ModelUpdate(cb,SIGNAL(currentIndexChanged(int)),index);
		return cb;
	}
	else if(index.column()==2)
	{
		amyColorButton* btn=new amyColorButton(parent);
		this->ConnectWidget2ModelUpdate(btn,SIGNAL(s_colorchanged()),index);
		return btn;
	}
}


void DataRoleTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if(index.column()==0)
	{
		int value = index.model()->data(index, Qt::DisplayRole).toInt();
		QComboBox *cb = static_cast<QComboBox*>(editor);
		cb->setCurrentIndex(value);
	}
	else if(index.column()==1)
	{
		int value = index.model()->data(index, Qt::DisplayRole).toInt();
		QComboBox *sb = static_cast<QComboBox*>(editor);
		sb->setCurrentIndex(value);
	}
	else if(index.column()==2)
	{
		amyColorButton *sb = static_cast<amyColorButton*>(editor);
		QColor c=index.model()->data(index, Qt::DisplayRole).value<QColor>();
		sb->SetColor(c);
	}
}
void DataRoleTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	if(index.column()==0)
	{
		QComboBox *cb = static_cast<QComboBox*>(editor);
		int value=cb->currentIndex();
		model->setData(index, value);
	}
	else if(index.column()==1)
	{
		QComboBox *sb = static_cast<QComboBox*>(editor);
		int value=sb->currentIndex();
		model->setData(index, value);
	}
	else if(index.column()==2)
	{
		amyColorButton *sb = static_cast<amyColorButton*>(editor);
		QColor value=sb->GetColor();
		model->setData(index, value);
	}
}

void DataRoleTableDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

void DataRoleTableDelegate::paint(QPainter *painter,  
	const QStyleOptionViewItem &option,  
	const QModelIndex &index) const
{
	QWidget *w;
	if(index.column()==0)
	{
		int value=index.data().toInt();
		QStyleOptionComboBox* editor=new QStyleOptionComboBox;
		editor->rect=option.rect;
		if(value==0)
			editor->currentText="X";
		else
			editor->currentText="Y";
		editor->state = option.state;
		editor->state |= QStyle::State_Enabled;
		editor->rect=option.rect;
		QApplication::style()->drawComplexControl(QStyle::CC_ComboBox,editor, painter);
		QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel,editor, painter);
		//delete cb;
	}
	else if(index.column()==1)
	{
		QStyleOptionComboBox *editor = new QStyleOptionComboBox;
		editor->rect=option.rect;
		editor->state = option.state;
		editor->state |= QStyle::State_Enabled;
		editor->currentText=index.data().toString();
		QApplication::style()->drawComplexControl(QStyle::CC_ComboBox,editor, painter);
		QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel,editor, painter);
		//delete editor;
	}
	
	 
	//QItemDelegate::paint(painter,option,index);
}


void amyDataEditor::keyTablePressEvent( QKeyEvent * event)
{
	if(event->matches(QKeySequence::Copy))
	{
		Copy();
	}
}
bool amyDataEditor::eventFilter(QObject *target, QEvent *event)
{
	if(target==this->m_Table)
	{
		if(event->type()==QEvent::KeyPress)
		{
			keyTablePressEvent(static_cast<QKeyEvent*>(event));
			return 1;
		}
	}
	return amyVariableEditor::eventFilter(target,event);
}
void amyDataEditor::Copy()
{
	amyVariable v=this->GetInput();
	int  cc=m_Table->columnCount();
	int  rc=m_Table->rowCount();
	QString str="";
	for(int i=0;i<rc;i++)
	{
		for(int j=0;j<cc;j++)
		{
			QModelIndex index=m_Table->model()->index(i,j);
			if(m_Table->selectionModel()->isSelected(index))
			{
				str+=QString::number(index.data().toFloat());
				str+="\t";
			}
		}
		str+="\n";
	}
	QApplication::clipboard()->setText(str);
}