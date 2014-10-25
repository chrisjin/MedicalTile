#include "amyFolderView.h"
#include "amyDICOMFolder.h"
#include "amyDICOM.h"
#include "amyPatientModel.h"
#include<QHeaderView>
#include<qfile.h>
#include<QScrollBar>
#include"amyPatientTable.h"
#include<QMouseEvent>
#include<QApplication>
#include"amyDragData.h"
#include<qDebug>
#include"amyTypeWrap.h"
#include"amyShuttle.h"
#include<QMessageBox>
#include"amySeriesSet.h"
amyFolderView::amyFolderView(QWidget *parent)
	: QTabWidget(parent)
{
	this->SetSender(this->tabBar());
	//this->setSizePolicy
	this->setFixedWidth(210);
	//this->tabBar()->installEventFilter(this);
	this->setAcceptDrops(1);
}
void amyFolderView::OnTakeOff(QPoint pos)
{
	int SelectedTabIndex=this->tabBar()->tabAt(pos);
	QPixmap pix(":/ICON/Patient");
	pix=pix.scaled(64,64);
	amySeriesSet::Keeper ss=amySeriesSet::New();
	qDebug()<<QString::number(this->m_Folder->GetPatientArr().size())<<endl;
	amyKeeper<amyPatient> pt=this->m_Folder->GetPatientArr()[SelectedTabIndex];
	for(int i=0;i<pt->seriesarr.size();i++)
	{
		ss->seriesarr.push_back(pt->seriesarr[i]);
	}
	amyShuttle::GetInstance()->SendData(VTYPE_SERIES_SET,ss,pix,this);
}
void amyFolderView::SetFolder(amyKeeper<amyDCMFolder> folder)
{
	for(int i=0;i<m_PatientViewArr.size();i++)
	{
		delete m_PatientViewArr[i];
	}
	m_Folder=folder;
	m_PatientViewArr.clear();
	this->clear();
	this->setTabPosition(QTabWidget::West); 
	for(int i=0;i<folder->GetPatientArr().size();i++)
	{
		amyPatient::Keeper pat=folder->GetPatientArr()[i];
		amyPatientTable *view=new amyPatientTable(pat.GetPointer());
		QHeaderView* verticalHeader = view->verticalHeader();
		verticalHeader->setResizeMode(QHeaderView::Fixed);
		verticalHeader->setDefaultSectionSize(64);

		QHeaderView* horizontalHeader = view->horizontalHeader();
		horizontalHeader->hide();
		horizontalHeader->setResizeMode(QHeaderView::Fixed);
		horizontalHeader->setDefaultSectionSize(150);;

		this->addTab(view,pat->info->name.c_str());
		
		m_PatientViewArr.push_back(view);
	}
}
amyFolderView::~amyFolderView()
{
	for(int i=0;i<m_PatientViewArr.size();i++)
	{
		delete m_PatientViewArr[i];
	}
}

void amyFolderView::dropEvent(QDropEvent *event)
{
	VTYPE type=amyShuttle::GetInstance()->GetType();
	if(type!=VTYPE_SERIES_SET)
		return;
	amySeriesSet::Keeper ks=amyShuttle::GetInstance()->GetData().CastTo<amySeriesSet>();
	amySeriesSet* sst=ks.GetPointer();
	if(this->m_Folder.IsNull())
	{
		this->m_Folder=new amyDCMFolder;
	}
	this->m_Folder->InsertSeriesSet(ks);
	this->SetFolder(m_Folder);
//	if(!ks.IsNull())
//	{
//		amyPatient::Keeper kp=amyUtil::MakePatientFromSeriesSet(ks);
//		for(int i=0;i<this->m_Folder->GetPatientArr().size();i++)
//		{
//			for(int j=0;j<m_Folder->GetPatientArr()[i]->seriesarr.size();j++)
//			{
//				for(int k=0;k<kp->seriesarr.size();k++)
//				{
//					if(kp->seriesarr[k]==m_Folder->GetPatientArr()[i]->seriesarr[j])
//					{
//						goto BAD_END;
//					}
//				}
//			}
//		}
//
//GOOD_END:
//		{
//			amyPatientTable *view=new amyPatientTable(kp.GetPointer());
//			QHeaderView* verticalHeader = view->verticalHeader();
//			verticalHeader->setResizeMode(QHeaderView::Fixed);
//			verticalHeader->setDefaultSectionSize(64);
//
//			QHeaderView* horizontalHeader = view->horizontalHeader();
//			horizontalHeader->hide();
//			horizontalHeader->setResizeMode(QHeaderView::Fixed);
//			horizontalHeader->setDefaultSectionSize(150);;
//
//			this->addTab(view,kp->info->name.c_str());
//
//			m_PatientViewArr.push_back(view);
//		}
//		return;
//BAD_END:
//		{
//		QMessageBox::warning(this,"Warn","Already Included!");
//		return;
//		}
//	}//if(!ks.IsNull())
//
}

void amyFolderView::dragEnterEvent(QDragEnterEvent *event)
{
	VTYPE type=amyShuttle::GetInstance()->GetType();
	if(type!=VTYPE_SERIES_SET)
		return;
	else
	{
		event->acceptProposedAction();
	}
}