#include "amyPatientTable.h"
#include<QMouseEvent>
#include<QApplication>
#include"amyDICOM.h"
#include"amyPatientModel.h"
#include"amyDragData.h"
#include<QFile>
#include"amyShuttle.h"
#include"amySeriesManager.h"
amyPatientTable::amyPatientTable(amyPatient* pat,QWidget *parent)
	: QTableView(parent)
{
	this->setSelectionMode(QTableView::SingleSelection);
	this->SetSender(this->viewport());
	m_Patient=pat;
	m_Model=new amyPatientModel(pat,this);
	this->setModel(m_Model);
	this->setItemDelegate(new amySeriesDelegate(pat,this));
	
	QFile file(":/QSS/ScrollStyle");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString stylestr=file.readAll();
	this->setStyleSheet(stylestr);
}

amyPatientTable::~amyPatientTable()
{

}

void amyPatientTable::OnTakeOff(QPoint pos)
{
	QModelIndex index=this->indexAt(QPoint(pos.x(),pos.y()));
	int serindex=qVariantValue<int>(m_Model->data(index,Qt::DisplayRole));
	amyKeeper<amySeries> ser=this->m_Patient->seriesarr[serindex];
	QImage*    thumb=amySeriesManager::GetInstance()->GetThumb(ser.GetPointer());
	if(!ser.IsNull())
	{
		QPixmap pix=QPixmap::fromImage(*thumb);
		amyShuttle::GetInstance()->SendData(VTYPE_SERIES,ser,pix,this);
	}
	else
	{
	}
}

