#include"amyShuttle.h"
#include<QDrag>
#include<QMimeData>
IMPLEMENT_SINGLETON(amyShuttle)
amyShuttle::amyShuttle()
{

}
void amyShuttle::SendData(VTYPE type,amyKeeper<void> data,QWidget* sender)
{
	QDrag *drag = new QDrag(sender);
	QMimeData *mimeData = new QMimeData;
	drag->setMimeData(mimeData);

	SetData(type,data,sender);
	Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
	ClearData();
}
void amyShuttle::SendData(VTYPE type,amyKeeper<void> data,QPixmap pix,QWidget* sender)
{
	QDrag *drag = new QDrag(sender);
	QMimeData *mimeData = new QMimeData;
	drag->setMimeData(mimeData);

	pix=pix.scaled(64,64);
	drag->setPixmap(pix);
	
	SetData(type,data,sender);
	Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
	ClearData();
	
}
amyKeeper<void> amyShuttle::GetData()
{
	amyKeeper<void> data=m_Data;
	amyKeeper<void> nulldata;
	this->SetData(VTYPE_NULL,nulldata,0);
	return data;
}

void amyShuttle::SetData(VTYPE type,amyKeeper<void> data,QWidget* sender)
{
	m_Data=data;
	m_Type=type;
	m_Sender=sender;
}

void amyShuttle::ClearData()
{
	amyKeeper<void> vnull;
	SetData(VTYPE_NULL,vnull,0);
}