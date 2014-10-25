#include"amySeriesSetEditor.h"
#include"amyQUtil.h"
#include<QBoxLayout>
#include<QLabel>
#include<QPainter>
#include"amySeriesSet.h"
#include"amySeriesManager.h"
#include"amyDICOM.h"
#include<QEvent>
#include<QContextMenuEvent>
#include<QMenu>
#include<QPainter>
#include"amyCube.h"
#include"amySeriesManager.h"
#include<QMessageBox>
#include"amyAlgorithmProgress.h"
amySeriesWidget::amySeriesWidget(amyKeeper<amySeries> ser,QWidget* p):QWidget(p)
{
	m_IsDeleted=0;
	m_Series=ser;
	QImage* img=pSeriesManager->GetThumb(ser);
	if(img)
		m_Thumb=QPixmap::fromImage(*img).scaled(64,64);
	QPainter drawtext(&m_Thumb);
	drawtext.setPen(Qt::green);
	drawtext.drawText(m_Thumb.rect(),Qt::AlignBottom,\
		QString::number(ser->slicearr.size()));


	m_DeletedThumb=m_Thumb.copy();

	QPainter painter(&m_DeletedThumb);
	QPen pen;
	pen.setWidth(3);
	pen.setColor(Qt::red);
	pen.setStyle(Qt::DashLine);
	painter.setPen(pen);
	QRect r=m_DeletedThumb.rect();
	painter.drawLine(r.topLeft(),r.bottomRight());
	painter.drawLine(r.topRight(),r.bottomLeft());


	QVBoxLayout* l=new QVBoxLayout; 
	l->setSpacing(0);
	//l->setContentsMargins(0,0,0,0);
	this->setLayout(l);
	
	m_Label=new QLabel(this);

	m_Label->setPixmap(m_Thumb);
	this->layout()->addWidget(m_Label);
}
void amySeriesWidget::SetDelete(bool v)
{
	m_IsDeleted=v;
	if(v==1)
	{
		m_Label->setPixmap(m_DeletedThumb);
	}
	else if(v==0)
	{
		m_Label->setPixmap(m_Thumb);
	}
	m_Label->repaint();
}
void amySeriesWidget::paintEvent(QPaintEvent* e)
{
	//QPainter p(this);
	//QPixmap pix=QPixmap::fromImage(*m_Thumb);
	//p.drawpix;
}
amySeriesWidget::~amySeriesWidget()
{
}


amySeriesSetEditor::amySeriesSetEditor(QWidget *parent):amyVariableEditor(parent)
{
	m_Table=new QTableWidget(parent);
	m_Table->installEventFilter(this);
	connect(this,SIGNAL(accepted()),this,SLOT(AfterConfirm()));
}

void amySeriesSetEditor::InitInput()
{
	amyVariable v=this->GetInput();
	FETCH(amySeriesSet,set,v);
	m_Table->setColumnCount(6);
	m_Table->setRowCount(set.seriesarr.size()/5+1);
	for(int i=0;i<m_Table->rowCount();i++)
	{
		m_Table->setRowHeight(i,80);
		for(int j=0;j<m_Table->columnCount();j++)
		{
			m_Table->setColumnWidth(j,80);
			int index=i*6+j;
			if(index<set.seriesarr.size()&&index>=0)
				m_Table->setCellWidget(i,j,new amySeriesWidget(set.seriesarr[index],this));
			else
				break;
		}
	}
	this->GetMainWidget()->setLayout(new QVBoxLayout);
	this->GetMainWidget()->layout()->addWidget(m_Table);

	this->resize(560,500);
	amyVariableEditor::InitInput();
}

bool amySeriesSetEditor::eventFilter(QObject *obj, QEvent *event)
{
	if(m_Table==obj)
	{
		QEvent::Type t=event->type();
		if(event->type()==QEvent::ContextMenu)
		{
			contextTableMenuEvent(static_cast<QContextMenuEvent*>(event));
		}
	}
	return QObject::eventFilter(obj,event);
}
void amySeriesSetEditor::contextTableMenuEvent(QContextMenuEvent *e)
{
	QMenu* m=new QMenu(this);
	{
		QAction *a=new QAction("Delete",m);
		m->addAction(a);
		connect(a,SIGNAL(triggered()),this,SLOT(DeleteTableCell()));
	}
	{
		QAction *a=new QAction("Recover",m);
		m->addAction(a);
		connect(a,SIGNAL(triggered()),this,SLOT(RecoverTableCell()));
	}
	m->exec(QCursor::pos());
}

void amySeriesSetEditor::DeleteTableCell()
{
//	QModelIndexList l=this->m_Table->selectionModel()->selectedIndexes();
	
	for(int i=0;i<m_Table->rowCount();i++)
	{
		for(int j=0;j<m_Table->columnCount();j++)
		{
			QModelIndex index=m_Table->model()->index(i,j);
			if(m_Table->selectionModel()->isSelected(index))
			{
				amySeriesWidget* w=(amySeriesWidget*)m_Table->cellWidget(i,j);
				if(w)
				{
					w->SetDelete(1);
				}
			}
		}
	}
}
void amySeriesSetEditor::RecoverTableCell()
{
	for(int i=0;i<m_Table->rowCount();i++)
	{
		for(int j=0;j<m_Table->columnCount();j++)
		{
			QModelIndex index=m_Table->model()->index(i,j);
			if(m_Table->selectionModel()->isSelected(index))
			{
				amySeriesWidget* w=(amySeriesWidget*)m_Table->cellWidget(i,j);
				if(w)
				{
					w->SetDelete(0);
				}
			}
		}
	}
}
void amySeriesSetEditor::Confirm()
{
	amyVariable v=this->GetInput();
	FETCH(amySeriesSet,set,v);
	vector<amySeries::Keeper> kser;
	vector<amyCube::Keeper>   kcub;
	for(int i=0;i<m_Table->rowCount();i++)
	{
		for(int j=0;j<m_Table->columnCount();j++)
		{
			amySeriesWidget* w=(amySeriesWidget*)m_Table->cellWidget(i,j);
			if(w)
			{
				if(!w->IsDeleted())
				{
					amySeries::Keeper ser=w->GetSeries();
					kser.push_back(ser);
					if(pSeriesManager->HasCube(ser))
					{
						kcub.push_back(pSeriesManager->GetCube(ser));
					}
				}
			}

		}
	}
	set.seriesarr=kser;
	set.cubearr=kcub;
}

void amySeriesSetEditor::AfterConfirm()
{
	QString con="If you want to LOAD the SERIESes into memory,plz push yes!\nThis will accelerate the following operation greatly!";
	QMessageBox::StandardButton b=QMessageBox::information(this,"Attetion",con,QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if(b==QMessageBox::Yes)
	{
		amyVariable v=this->GetInput();
		FETCH(amySeriesSet,set,v);
		amySeriesSet::Keeper pserarr=v.Get<amySeriesSet>();
		pProgress->SetStepCount(pserarr->seriesarr.size());
		pProgress->Begin();
		for(int i=0;i<pserarr->seriesarr.size();i++)
		{
			amyCube::Keeper cu=amySeriesManager::GetInstance()->GetCube(pserarr->seriesarr[i]);
			pserarr->cubearr.push_back(cu);
			pProgress->Step();
		}
		pProgress->End();
	}
}