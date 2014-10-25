#include "amyPatientModel.h"
#include "amyDICOM.h"
#include"amyQUtil.h"
#include"dcmtk\dcmimgle\dcmimage.h"
#include<Qt\qicon.h>
#include<QStyleOptionViewItem>
#include<qevent>
#include<qpainter>
#include"amySeriesManager.h"
amyPatientModel::amyPatientModel(amyPatient* pat,QObject *parent): QAbstractTableModel(parent)
{
	this->m_Patient=pat;
	this->m_RowCount=pat->seriesarr.size();
}
bool amyPatientModel::setData(QModelIndex const& idx, QVariant const& value, int role)
{
  if (Qt::EditRole == role)
  {
    // Update data...

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();

    return true;
  }
  return false;
}

amyPatientModel::~amyPatientModel()
{
}

int amyPatientModel::rowCount(const QModelIndex &parent)const
{
	return m_RowCount;
}
int	amyPatientModel::columnCount ( const QModelIndex & parent) const
{
	return 1;
}
QVariant amyPatientModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::DisplayRole&&index.row()<m_Patient->seriesarr.size())
	{
		return QVariant::fromValue(index.row());
	}
	else
		return QVariant();
}
QVariant amyPatientModel::headerData(int section, Qt::Orientation orientation,int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal&&m_Patient)
	{
		if(m_Patient)
			return m_Patient->info->name.c_str();
		else
			return "";
	}
	else
	{
		return QString("%1").arg(section+1);
	}
}


amySeriesDelegate::amySeriesDelegate(amyPatient* pat,QObject * parent)
:QItemDelegate(parent)
{
	m_Patient=pat;
}

void amySeriesDelegate::paint(QPainter *painter,  
                          const QStyleOptionViewItem &option,  
                          const QModelIndex &index) const  
{  
    if (index.column() == 0) {  
		int serindex=qVariantValue<int>(index.data());
		if(serindex>=this->m_Patient->seriesarr.size())
			return;
		amySeries* ser=this->m_Patient->seriesarr[serindex].GetPointer();
		QImage* seriesthumb=amySeriesManager::GetInstance()->GetThumb(ser);
		ser->info->acquisitiontime.hour;
		QString year = QString("%1-%2-%3")
			.arg(ser->info->date.year,4, 10, QChar('0'))    
			.arg(ser->info->date.month, 2, 10, QChar('0'))
			.arg(ser->info->date.day,2,10,QChar('0')); 
		QString time = QString("%1:%2:%3")    
			.arg(ser->info->acquisitiontime.hour, 2, 10, QChar('0'))    
			.arg(ser->info->acquisitiontime.minute, 2, 10, QChar('0'))
			.arg(ser->info->acquisitiontime.second,2,10,QChar('0'));  
		QString imagecount = QString("COUNT:%1")
			.arg(ser->slicearr.size()) ;

		QRect rect=option.rect;    
		int x=rect.x();    
		int y=rect.y();  
		if(seriesthumb)
		{
			QPixmap pixmap=QPixmap::fromImage(*seriesthumb);
			painter->drawPixmap(x,y,rect.height(),rect.height(),pixmap);
		}
		QStyleOptionViewItem myOption = option;  
		myOption.rect.setLeft(rect.height());
		
		myOption.displayAlignment = Qt::AlignRight | Qt::AlignTop;
		drawDisplay(painter, myOption, myOption.rect, year);  
		myOption.displayAlignment = Qt::AlignRight | Qt::AlignBottom;
		drawDisplay(painter, myOption, myOption.rect, time);  
		myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
		drawDisplay(painter, myOption, myOption.rect, imagecount);  
    } else{   
        QItemDelegate::paint(painter, option, index);  
    }  
}  

bool amySeriesDelegate::editorEvent(QEvent * event,  
                                 QAbstractItemModel * model,  
                                 const QStyleOptionViewItem & /*option*/,  
                                 const QModelIndex & index)  
{  
    if(event->type()==QEvent::MouseButtonPress &&  
        index.column()==0){  
/*            QVariant var=model->data(index,Qt::CheckStateRole);  
            bool isFavourite=var.toBool();  
            if(var.isValid())  
                isFavourite=isFavourite?false:true;  
            else  
                isFavourite=true;  
            model->setData(index,isFavourite,Qt::CheckStateRole);*/  
            return true;//I have handled the event  
    }  
  
    return false;  
} 