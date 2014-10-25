#include "amyVariableArea.h"
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
amyVariableArea::amyVariableArea(QWidget *parent)
	: amyCanvas(parent)
{
	this->setWindowTitle("Cuisine");
	
	
	this->setAcceptDrops(true);

	QPalette p=this->palette();
	this->setAutoFillBackground(true);
	p = this->palette();
	//p.setColor(QPalette::Window,QColor(100,100,100));
	p.setColor(QPalette::Window,QColor(156,170,193));
	this->setPalette(p);

	m_BeginToSelect=0;
	m_DragedLing=0;
	//this->setFixedSize(800,300);
}

amyVariableArea::~amyVariableArea()
{

}
void amyVariableArea::AddVariable(amyVariable v,int x,int y)
{
	amyVariableLing* ling=new amyVariableLing(this);
	ling->SetPosition(x,y);
	ling->SetInput(v);
	m_VariableLingSet.insert(ling);
	this->repaint();
}
void amyVariableArea::AddVariableArr(vector<amyVariable>& varr,int x,int y)
{
	for(int i=0;i<varr.size();i++)
	{
		this->AddVariable(varr[i],x,y);
		x+=80;
	}
}
void amyVariableArea::dropEvent(QDropEvent *event)
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
QPoint ContextPos;
void amyVariableArea::contextMenuEvent(QContextMenuEvent *event)
{
	//////////////////////
	///¼ûQAMYCuisineWindow
	//////////////////////
	m_ContextMenuPos=event->pos();
}
void amyVariableArea::dragEnterEvent(QDragEnterEvent *event)
{
	if(amyShuttle::GetInstance()->GetSender()!=this)
		event->acceptProposedAction();
}
void amyVariableArea::dragMoveEvent(QDragMoveEvent *event)
{

}
void amyVariableArea::UpdateLingSelection()
{
	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
	this->m_SelectedLingArr.clear();
	for(;itr!=m_VariableLingSet.end();itr++)
	{
		if((*itr)->IsActivated())
			this->m_SelectedLingArr.push_back(itr);
	}
}
void amyVariableArea::UpdateVariableSelection()
{
	UpdateLingSelection();
	for(int i=0;i<m_SelectedLingArr.size();i++)
	{
		m_SelectedVariable.push_back((*m_SelectedLingArr[i])->GetInput());
	}
}
void amyVariableArea::paintEvent(QPaintEvent *event)
{
	if(m_BeginToSelect)
	{
		QPainter p(this);
		QPen pen(Qt::DashDotDotLine);
		pen.setColor(QColor(100,100,100));
		p.setPen(pen);
		p.drawRect(m_SelectionRect);
	}
	amyCanvas::paintEvent(event);
}
void amyVariableArea::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons()&Qt::RightButton)
	{
		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
		for(;itr!=m_VariableLingSet.end();itr++)
		{
			if((*itr)->IsContain(event->x(),event->y()))
			{
				if(!(*itr)->IsActivated())
					(*itr)->SetActivated(1);
			}
		}
	}
	if(event->buttons()&Qt::LeftButton)
	{
		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
		bool flag=0;
		if(m_DragedLing==0)
		{
			for(;itr!=m_VariableLingSet.end();itr++)
			{
				if((*itr)->IsContain(event->x(),event->y()))
				{
					m_DragedLing=(*itr);
					m_DragedLing->SetActivated(1);
					flag=1;
				}
				else
				{
					(*itr)->SetActivated(0);
				}
			}
			this->repaint();
		}
		if(!flag)
		{
			//itr=m_VariableLingSet.begin();
			//for(;itr!=m_VariableLingSet.end();itr++)
			//{
			//	(*itr)->SetActivated(0);
			//}

			m_BeginToSelect=1;
			m_BeginPoint=event->pos();
		}
	}
	//this->repaint();
	amyCanvas::mousePressEvent(event);
}
void amyVariableArea::mouseMoveEvent(QMouseEvent * event)
{
	//if(!this->rect().contains(event->pos()))
	//{
	//	//qDebug()<<"OUTTTTT"<<endl;
	//	mouseLeaveEvent(event);
	//}
	if(m_BeginToSelect)
	{
		int x1=m_BeginPoint.x()<event->x()?m_BeginPoint.x():event->x();
		int y1=m_BeginPoint.y()<event->y()?m_BeginPoint.y():event->y();
		int x2=m_BeginPoint.x()>event->x()?m_BeginPoint.x():event->x();
		int y2=m_BeginPoint.y()>event->y()?m_BeginPoint.y():event->y();
		m_SelectionRect.setTopLeft(QPoint(x1,y1));
		m_SelectionRect.setBottomRight(QPoint(x2,y2));
		set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
		for(;itr!=m_VariableLingSet.end();itr++)
		{
			if((*itr)->IsIn(amyRect(m_SelectionRect.x(),m_SelectionRect.y(),
				m_SelectionRect.width(),m_SelectionRect.height())))
				(*itr)->SetActivated(1);
			else
				(*itr)->SetActivated(0);
		}
		
		
		repaint();
	}
	amyCanvas::mouseMoveEvent(event);
}
void amyVariableArea::mouseReleaseEvent(QMouseEvent *event)
{
	m_BeginToSelect=0;
	m_DragedLing=0;
	repaint();
	amyCanvas::mouseReleaseEvent(event);
}
void amyVariableArea::leaveEvent ( QEvent * event )
{
	m_DragedLing=0;
	m_BeginToSelect=0;
	//if(!m_DragedLing)
	//	return;
	//QPixmap pix;
	//QDrag *drag = new QDrag(this);
	////amyDragData::GetInstance()->SetData(VTYPE_SERIES,m_CurrentData->series);;
	//QMimeData *mimeData = new QMimeData;
	//drag->setMimeData(mimeData);
	//if(m_DragedLing)
	//pix=QPixmap::fromImage(*m_DragedLing->GetThumb());
	////QPixmap pix=GetDragIcon();
	//pix=pix.scaled(64,64);
	////pix.scaledToWidth(16);
	////pix.scaledToHeight(16);
	//drag->setPixmap(pix);
	//Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
	//m_DragedLing=0;
}
void amyVariableArea::mouseLeaveEvent(QMouseEvent *event)
{
	if(!m_DragedLing)
		return;
	QPixmap pix;
	amyVariable v=m_DragedLing->GetInput();
	if(m_DragedLing)
	pix=QPixmap::fromImage(m_DragedLing->GetThumb());
	pix=pix.scaled(64,64);
	amyShuttle::GetInstance()->SendData(v.GetType(),v.Get(),pix,this);

	m_DragedLing=0;
	m_BeginToSelect=0;
}
void amyVariableArea::DeleteSelected()
{
	this->UpdateLingSelection();
	for(int i=0;i<this->m_SelectedLingArr.size();i++)
	{
		amyVariableLing* p=*m_SelectedLingArr[i];
		m_VariableLingSet.erase(m_SelectedLingArr[i]);
		this->RemoveLing(p);
		delete p;
	}

	m_SelectedLingArr.clear();
	m_SelectedVariable.clear();
	this->repaint();
}

vector<amyVariableArea::tIterator>& amyVariableArea::GetSelectedLing()
{
	return m_SelectedLingArr;
}

void amyVariableArea::GetSelectedLingArr(vector<amyVariableLing*>& lingarr)
{
	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
	for(;itr!=m_VariableLingSet.end();itr++)
	{
		if((*itr)->IsActivated())
			lingarr.push_back((*itr));
	}
}
void amyVariableArea::GetSelectedVariableArr(vector<amyVariable>& vararr)
{
	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
	for(;itr!=m_VariableLingSet.end();itr++)
	{
		if((*itr)->IsActivated())
			vararr.push_back((*itr)->GetInput());
	}
}

void amyVariableArea::GetLingArrAt(int x,int y,vector<amyVariableLing*>& lingarr)
{
	set<amyVariableLing*>::iterator itr=m_VariableLingSet.begin();
	for(;itr!=m_VariableLingSet.end();itr++)
	{
		if((*itr)->IsContain(x,y))
		{
			lingarr.push_back((*itr));
		}
	}
}
