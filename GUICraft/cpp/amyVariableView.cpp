#include "amyVariableView.h"
#include<QDragEnterEvent>
#include"amyDragData.h"
#include"amyVariableManager.h"
#include"amyCube.h"
#include"amyVariableLing.h"
#include<QPainter>
#include<QLinearGradient>
#include<qDebug>
#include"amyAlgorithmStack.h"
//#include"amyAlgorithmManager.h"
#include<QMenu>
#include"amyDICOM.h"
#include"amyVariableManager.h"
#include"amyVariableEditor.h"
#include<QFileDialog>
#include<QSettings>
#include"amySeriesManager.h"
#include"amyTypeWrap.h"
#include"amyAlgorithmBridge.h"
#include<QUrl>
#include"amyShuttle.h"
#include"amySeriesSet.h"
#include<QGraphicsScene>
#include<QGraphicsSceneContextMenuEvent>
#include<QGraphicsSceneMouseEvent>
//void amyVariableScene::contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent)
//{
//	emit s_contextmenu(contextMenuEvent->pos());
//}
void amyVariableScene::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	 if (event->button() != Qt::LeftButton) 
	 {
		 if(event->button()==Qt::RightButton)
		 {
			 QGraphicsItem* item=this->itemAt(event->scenePos());
			 if(item)
			 {
				 if(!item->isSelected())
				 {
					 clearSelection();
					 item->setSelected(1);
				 }
				 //item->update();
				 //item->SetActivated(1);
			 }
		 }
		event->accept();
        return;
    }
    QGraphicsScene::mousePressEvent(event);
}

amyVariableView::amyVariableView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setWindowTitle("Cuisine");
	
	
	this->setAcceptDrops(true);

	//QPalette p=this->palette();
	//this->setAutoFillBackground(true);
	//p = this->palette();
	this->setBackgroundBrush(QBrush(QColor(156,170,193)));
	//p.setColor(QPalette::Window,QColor(100,100,100));
	//p.setColor(QPalette::Window,QColor(156,170,193));
	//this->setPalette(p);
	this->setRubberBandSelectionMode(Qt::ItemSelectionMode::ContainsItemBoundingRect);
	m_Scene=new amyVariableScene(this);
	this->setScene(m_Scene);

	this->setDragMode(QGraphicsView::RubberBandDrag);

	this->viewport()->installEventFilter(this);
	//this->setFixedSize(800,300);

	setSceneRect(this->rect());
	//QRect tr=this->frameGeometry();
	m_Scene->setSceneRect(this->rect());
	//QRectF r=m_Scene->sceneRect();

	//connect(m_Scene,SIGNAL(s_contextmenu(QPointF)),this,SLOT(ContextSceneMenu(QPointF)));
}

amyVariableView::~amyVariableView()
{

}
//void amyVariableView::ContextSceneMenu(QPointF p)
//{
//	QPoint viewp=this->mapFromScene(p);
//	emit s_contextmenu(viewp);
//}
void amyVariableView::AddVariable(amyVariable v,int x,int y)
{
	QPointF pos=this->mapToScene(x,y);
	amyVariableItem* item=new amyVariableItem();
	item->SetInput(v);
	item->setPos(pos.x(),pos.y());
	m_Scene->addItem(item);
}
void amyVariableView::GetItemPosition(amyVariableItem* item,int& x,int& y)
{
	QPointF pos=item->pos();
	QPoint viewpos=this->mapFromScene(pos);
	x=viewpos.x();
	y=viewpos.y();
}
void amyVariableView::AddVariableArr(vector<amyVariable>& varr,int x,int y)
{
	for(int i=0;i<varr.size();i++)
	{
		this->AddVariable(varr[i],x,y);
		x+=80;
	}
}
void amyVariableView::dropEvent(QDropEvent *event)
{
	const QMimeData* mmd=event->mimeData();
	if(mmd)
	{
		QList<QUrl> urls=mmd->urls();
		for(int i=0;i<urls.size();i++)
		{
			QUrl u=urls.at(i);
			QString str=u.toLocalFile();
			amyVariableManager* tm=amyVariableManager::GetInstance();
			vector<amyVariable> varr;
			tm->Deserialize(str,varr);
			this->AddVariableArr(varr,event->pos().x()+i*80,event->pos().y());
		}
	}
	
	if(this==amyShuttle::GetInstance()->GetSender())
	{
		return;
	}
	VTYPE type=amyShuttle::GetInstance()->GetType();
	switch(type)
	{
	case VTYPE_SERIES:
		{
			amyWatcher<amySeries> wser=amyShuttle::GetInstance()->GetData().CastTo<amySeries>();
			amySeriesManager* sm=amySeriesManager::GetInstance();
			amyCube::Keeper cube=sm->GetCube(wser);
			amyVariable v=amyVariable::New(cube,VTYPE_CUBE,"CUBE");
			AddVariable(v,event->pos().x(),event->pos().y());
		}
		//amyCube* cube=(amyCube*)v.Get();
		//cube->Open((amySeries*)amyDragData::GetInstance()->GetData());
		//amyVariableLing* ling=new amyVariableLing(this);
		//ling->SetPosition(event->pos().x(),event->pos().y());
		//ling->SetInput(v);
		//m_VariableLingSet.insert(ling);
		//this->repaint();
		break;
	case VTYPE_CUBE:
		{
			amyVariable v=amyVariable::New(VTYPE_CUBE,"CUBE");
			amyCube::Keeper dragdata=amyShuttle::GetInstance()->GetData().CastTo<amyCube>();
			amyCube::Keeper cube=v.Get<amyCube>();
			cube->Copy(dragdata.GetPointer());
			AddVariable(v,event->pos().x(),event->pos().y());
		}
		break;
	case VTYPE_SERIES_SET:
		{
			amySeriesSet::Keeper dragdata=amyShuttle::GetInstance()->GetData().CastTo<amySeriesSet>();
			if(dragdata->seriesarr.size()==0)
				break;
			string name;
			if(!dragdata->seriesarr[0]->patientinfo.IsNull())
				name=dragdata->seriesarr[0]->patientinfo->name;
			else
				name="SERIESSET";
			amyVariable v=amyVariable::New(VTYPE_SERIES_SET,name);
			amySeriesSet::Keeper ss=v.Get<amySeriesSet>();
			ss->seriesarr=dragdata->seriesarr;
			AddVariable(v,event->pos().x(),event->pos().y());
		}
		//amyCube* cube=(amyCube*)v.Get();
		//cube->Open((amySeries*)amyDragData::GetInstance()->GetData());
		//amyVariableLing* ling=new amyVariableLing(this);
		//ling->SetPosition(event->pos().x(),event->pos().y());
		//ling->SetInput(v);
		//m_VariableLingSet.insert(ling);
		//this->repaint();
		break;
	}
}
//QPoint ContextPos;
//void amyVariableView::contextMenuEvent(QContextMenuEvent *event)
//{
//	//////////////////////
//	///¼ûQAMYCuisineWindow
//	//////////////////////
//	QGraphicsView::contextMenuEvent(event);
//	emit s_contextmenu(event->pos());
//	m_ContextMenuPos=event->pos();
//	
//}
void amyVariableView::dragEnterEvent(QDragEnterEvent *event)
{
	if(amyShuttle::GetInstance()->GetSender()!=this)
		event->acceptProposedAction();
}
void amyVariableView::dragMoveEvent(QDragMoveEvent *event)
{
	////Override the Default
}

//void amyVariableView::mousePressEvent(QMouseEvent *event)
//{
//	if(event->buttons()&Qt::RightButton)
//	{
//		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//		for(;itr!=m_VariableLingSet.end();itr++)
//		{
//			if((*itr)->IsContain(event->x(),event->y()))
//			{
//				if(!(*itr)->IsActivated())
//					(*itr)->SetActivated(1);
//			}
//		}
//	}
//	if(event->buttons()&Qt::LeftButton)
//	{
//		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//		bool flag=0;
//		if(m_DragedLing==0)
//		{
//			for(;itr!=m_VariableLingSet.end();itr++)
//			{
//				if((*itr)->IsContain(event->x(),event->y()))
//				{
//					m_DragedLing=(*itr);
//					m_DragedLing->SetActivated(1);
//					flag=1;
//				}
//				else
//				{
//					(*itr)->SetActivated(0);
//				}
//			}
//			this->repaint();
//		}
//		if(!flag)
//		{
//			//itr=m_VariableLingSet.begin();
//			//for(;itr!=m_VariableLingSet.end();itr++)
//			//{
//			//	(*itr)->SetActivated(0);
//			//}
//
//			m_BeginToSelect=1;
//			m_BeginPoint=event->pos();
//		}
//	}
//	//this->repaint();
//	amyCanvas::mousePressEvent(event);
//}
//void amyVariableView::mouseMoveEvent(QMouseEvent * event)
//{
//	//if(!this->rect().contains(event->pos()))
//	//{
//	//	//qDebug()<<"OUTTTTT"<<endl;
//	//	mouseLeaveEvent(event);
//	//}
//	if(m_BeginToSelect)
//	{
//		int x1=m_BeginPoint.x()<event->x()?m_BeginPoint.x():event->x();
//		int y1=m_BeginPoint.y()<event->y()?m_BeginPoint.y():event->y();
//		int x2=m_BeginPoint.x()>event->x()?m_BeginPoint.x():event->x();
//		int y2=m_BeginPoint.y()>event->y()?m_BeginPoint.y():event->y();
//		m_SelectionRect.setTopLeft(QPoint(x1,y1));
//		m_SelectionRect.setBottomRight(QPoint(x2,y2));
//		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//		for(;itr!=m_VariableLingSet.end();itr++)
//		{
//			if((*itr)->IsIn(amyRect(m_SelectionRect.x(),m_SelectionRect.y(),
//				m_SelectionRect.width(),m_SelectionRect.height())))
//				(*itr)->SetActivated(1);
//			else
//				(*itr)->SetActivated(0);
//		}
//		
//		
//		repaint();
//	}
//	amyCanvas::mouseMoveEvent(event);
//}
//void amyVariableView::mouseReleaseEvent(QMouseEvent *event)
//{
//	m_BeginToSelect=0;
//	m_DragedLing=0;
//	repaint();
//	amyCanvas::mouseReleaseEvent(event);
//}
//void amyVariableView::leaveEvent ( QEvent * event )
//{
//	m_DragedLing=0;
//	m_BeginToSelect=0;
//	//if(!m_DragedLing)
//	//	return;
//	//QPixmap pix;
//	//QDrag *drag = new QDrag(this);
//	////amyDragData::GetInstance()->SetData(VTYPE_SERIES,m_CurrentData->series);;
//	//QMimeData *mimeData = new QMimeData;
//	//drag->setMimeData(mimeData);
//	//if(m_DragedLing)
//	//pix=QPixmap::fromImage(*m_DragedLing->GetThumb());
//	////QPixmap pix=GetDragIcon();
//	//pix=pix.scaled(64,64);
//	////pix.scaledToWidth(16);
//	////pix.scaledToHeight(16);
//	//drag->setPixmap(pix);
//	//Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
//	//m_DragedLing=0;
//}
bool amyVariableView::eventFilter(QObject *obj, QEvent *event)
{
	if(obj==this->viewport())
	{
		//if(event->type()==QEvent::Leave)
		//{
		//	mouseViewportLeaveEvent(static_cast<QMouseEvent*>(event));
		//}
		if(event->type()==QEvent::MouseMove)
		{
			mouseViewportMoveEvent(static_cast<QMouseEvent*>(event));
		}
	}
	return QGraphicsView::eventFilter(obj,event);
}
//void amyVariableView::mouseViewportLeaveEvent(QMouseEvent *event)
//{
//	amyVariableItem *item =(amyVariableItem *)m_Scene->mouseGrabberItem ();
//	if(!item)
//		return;
//	QPixmap pix;
//	amyVariable v=item->GetInput();
//	pix=QPixmap::fromImage(item->GetThumb());
//	pix=pix.scaled(64,64);
//	amyShuttle::GetInstance()->SendData(v.GetType(),v.Get(),pix,this);
//
//}
void amyVariableView::mouseViewportMoveEvent(QMouseEvent *event)
{
	if(!this->viewport()->rect().contains(event->pos()))
	{
		amyVariableItem *item =(amyVariableItem *)m_Scene->mouseGrabberItem ();
		if(!item)
			return;
		QPixmap pix;
		amyVariable v=item->GetInput();
		pix=QPixmap::fromImage(item->GetThumb());
		pix=pix.scaled(64,64);
		amyShuttle::GetInstance()->SendData(v.GetType(),v.Get(),pix,this);
		m_Scene->clearSelection();
		m_Scene->update();
	}
}

void amyVariableView::DeleteSelected()
{
	QList<QGraphicsItem*> l=m_Scene->selectedItems();
	for(int i=0;i<l.size();i++)
	{
		m_Scene->removeItem(l[i]);
		if(l[i])
			delete l[i];
	}
	//this->UpdateLingSelection();
	//for(int i=0;i<this->m_SelectedLingArr.size();i++)
	//{
	//	amyVariableLing* p=*m_SelectedLingArr[i];
	//	m_VariableLingSet.erase(m_SelectedLingArr[i]);
	//	this->RemoveLing(p);
	//	delete p;
	//}

	//m_SelectedLingArr.clear();
	//m_SelectedVariable.clear();
	//this->repaint();
}

//vector<amyVariableView::tIterator>& amyVariableView::GetSelectedLing()
//{
//	return m_SelectedLingArr;
//}

//void amyVariableView::GetSelectedLingArr(vector<amyVariableLing*>& lingarr)
//{
//	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//	for(;itr!=m_VariableLingSet.end();itr++)
//	{
//		if((*itr)->IsActivated())
//			lingarr.push_back((*itr));
//	}
//}
//void amyVariableView::GetSelectedVariableArr(vector<amyVariable>& vararr)
//{
//	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//	for(;itr!=m_VariableLingSet.end();itr++)
//	{
//		if((*itr)->IsActivated())
//			vararr.push_back((*itr)->GetInput());
//	}
//}

//void amyVariableView::GetLingArrAt(int x,int y,vector<amyVariableLing*>& lingarr)
//{
//	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
//	for(;itr!=m_VariableLingSet.end();itr++)
//	{
//		if((*itr)->IsContain(x,y))
//		{
//			lingarr.push_back((*itr));
//		}
//	}
//}

void amyVariableView::GetSelectedItemArr(vector<amyVariableItem*>& lingarr)
{
	QList<QGraphicsItem*> l=this->m_Scene->selectedItems();
	for(int i=0;i<l.size();i++)
	{
		lingarr.push_back((amyVariableItem*)l[i]);
	}
}

amyVariableItem* amyVariableView::GetItemAt(int x,int y)
{
	QPointF p=this->mapToScene(x,y);
	return (amyVariableItem*)this->m_Scene->itemAt(p);
}
void amyVariableView::GetItemArrAt(int x,int y,vector<amyVariableItem*>& lingarr)
{
	QList<QGraphicsItem*> arr=this->items(x,y);
	for(int i=0;i<arr.size();i++)
	{
		lingarr.push_back((amyVariableItem*)arr[i]);
	}
}
