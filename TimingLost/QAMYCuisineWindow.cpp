#include "QAMYCuisineWindow.h"
#include"amyVariableArea.h"
#include<QHBoxLayout>
#include"amyAlgorithmManager.h"
#include"amyAlgorithmStack.h"
#include"amyAlgorithm.h"
#include"amyDebug.h"
#include<algorithm>
#include"amyVariableLing.h"
#include"amyTypeWrap.h"
#include<QMessageBox> 
#include<QLabel>
#include<vector>
#include"amyEditorManager.h"
#include"amyVariableEditor.h"
#include"amyVariableManager.h"
#include<QSettings>
#include<QFileDialog>
#include<QSplitter>
#include<QSettings>
#include"amySplashScreen.h"
#include<QThread>
#include"amyAlgorithmThread.h"
#include<QProgressBar>
#include"amyAlgorithmProgress.h"
#include<QThreadPool>
#include"amyAlgorithmRunner.h"
#include"amyVariableView.h"
#include"amyAlgorithmMessager.h"
using namespace std;

#define ALGOTAB_INDEX "ALGOTAB_INDEX"
QAMYCuisineWindow::QAMYCuisineWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	QHBoxLayout* layout=new QHBoxLayout(this);
	ui.centralWidget->setLayout(layout);
	
	QSplitter* sp=new QSplitter(Qt::Horizontal,this);
	layout->addWidget(sp);
	
	
	amyAlgorithmManager* vm=amyAlgorithmManager::GetInstance() ;
	amySplashScreen::GetInstance()->showMessage("Loading: Algorithm Panel",Qt::AlignCenter);
	m_AlgoTab=vm->GetAlgorithmTab(sp);
	amySplashScreen::GetInstance()->showMessage("Loading: Algorithm Panel Done!!",Qt::AlignCenter);
	QSettings s;
	int curindex=s.value(ALGOTAB_INDEX,0).toInt();
	if(curindex<m_AlgoTab->count())
		m_AlgoTab->setCurrentIndex(curindex);

	sp->addWidget(m_AlgoTab);

	m_VariableArea=new amyVariableView(sp);
	m_VariableArea->viewport()->installEventFilter(this);
	//connect(m_VariableArea,SIGNAL(s_contextmenu(QPoint)),this,SLOT(ContextVariableViewMenu(QPoint)));
	sp->addWidget(m_VariableArea);
	
	QList<int> size;
	size.push_back(m_AlgoTab->minimumSizeHint().width());
	size.push_back(this->width()-m_AlgoTab->minimumSizeHint().width());
	sp->setSizes(size);

	//vector<string> catarr;
	//vm->GetCategoryList(catarr);
	//for(int i=0;i<catarr.size();i++)
	//{
	//	ui.menuBar->addMenu(vm->GetAlgorithmMenu(catarr[i].c_str(),this));
	//}
	


	connect(vm,SIGNAL(s_algorithmchoose(amyAlgorithm*)),
		this,SLOT(ApplyAlgorithm(amyAlgorithm*)));
	
	this->setWindowTitle("CuisineCraft");
	resize(1000,500);
	
	m_StatusMessage=new QLabel("Ready");
	m_StatusMessage->setStyleSheet("color:white");
	this->statusBar()->addPermanentWidget(m_StatusMessage,1);

	m_ProgressBar=new QProgressBar;
	m_ProgressBar->hide();
	this->statusBar()->addPermanentWidget(m_ProgressBar,1);
	connect(pProgress,SIGNAL(s_begin()),this,SLOT(BeginProgress()));
	connect(pProgress,SIGNAL(s_end()),this,SLOT(EndProgress()));
	connect(pProgress,SIGNAL(s_step(int)),this,SLOT(StepProgress(int)));

	
	amyAlgorithmRunner* ar=amyAlgorithmRunner::GetInstance();
	//connect(m_AlgorithmRunner,SIGNAL(s_invalid_inputtype()),this,SLOT(InvalidInputType()));
	//connect(m_AlgorithmRunner,SIGNAL(s_invalid_inputnum()),this,SLOT(InvalidInputNum()));
	//connect(m_AlgorithmRunner,SIGNAL(s_invalid_outputnum()),this,SLOT(InvalidOutputNum()));
	connect(ar,SIGNAL(s_begin_check),this,SLOT(InputCheckingBegin));
	connect(ar,SIGNAL(s_end_check),this,SLOT(InputCheckingEnd));
	connect(ar,SIGNAL(s_begin_run()),this,SLOT(AlgorithmBegin()));
	connect(ar,SIGNAL(s_end_run()),this,SLOT(AlgorithmEnd()));

	QPalette p=this->palette();
	this->setAutoFillBackground(true);
	p = this->palette();
	p.setColor(QPalette::Window,QColor(47,65,95));
	this->setPalette(p);

//	this->m_VariableArea->AddVariable(amyVariable::New(VTYPE_FLOAT_ARR,"ShuZu"),0,0);
}
void QAMYCuisineWindow::closeEvent(QCloseEvent *event)
{
	QSettings s;
	int in=m_AlgoTab->currentIndex();
	s.setValue(ALGOTAB_INDEX,in);
}
QAMYCuisineWindow::~QAMYCuisineWindow()
{

}

void QAMYCuisineWindow::ApplyAlgorithm(amyAlgorithm* algo)
{
	vector<amyVariableItem*> lings;
	m_VariableArea->GetSelectedItemArr(lings);
	//if(lings.size()==0)
	//{
	//	QMessageBox::information(0,"I TELL YOU","No Selected Item");
	//	return;
	//}
	vector<amyVariable> inputarr;
	if(lings.size()>0)
	{
		qSort(lings.begin(),lings.end(),ItemCompareLeft2Right);///从左到右
		for(int i=0;i<lings.size();i++)
		{
			inputarr.push_back(lings[i]->GetInput());
		}
	}
	vector<amyVariable> output;
	int flag=amyAlgorithmRunner::GetInstance()->Start(algo,inputarr,output);
	if(flag==0||amyAlgorithmMessager::GetInstance()->HasWarning())
	{
		amyAlgorithmMessager::GetInstance()->ShowAndClearAll();
		amyAlgorithmStack::GetInstance()->Clear();
		return;
	}

	////////检查输出位置是否有其他Ling
	int x=0,y=0;
	if(lings.size()>0)
		m_VariableArea->GetItemPosition(lings[lings.size()-1],x,y);
	int add=x+80;
	while(1)
	{
		lings.clear();
		m_VariableArea->GetItemArrAt(add,y,lings);
		if(lings.size()==0)
			break;
		else
			add+=80;
	}

	for(int i=0;i<output.size();i++)
	{
		m_VariableArea->AddVariable(output[i],add,y);
		add+=80;
	}
	
}

bool QAMYCuisineWindow::eventFilter(QObject *target, QEvent *event)
{
	if(target==this->m_VariableArea->viewport())
	{
		if(event->type()==QEvent::ContextMenu)
		{
			contextVariableAreaMenuEvent(static_cast<QContextMenuEvent*>(event));
		}
		if(event->type()==QEvent::MouseButtonDblClick)
		{
			mouseVariableAreaDoubleClickEvent(static_cast<QMouseEvent*>(event));
		}
	}
	return QMainWindow::eventFilter(target,event);
}
void QAMYCuisineWindow::mouseVariableAreaDoubleClickEvent(QMouseEvent * event)
{
	vector<amyVariableLing*> larr;
	amyVariableItem* item=m_VariableArea->GetItemAt(event->x(),event->y());
	if(item)
		EditVariable(item->GetInput());
}

void QAMYCuisineWindow::EditVariable(amyVariable& v)
{
	amyEditorManager* em=amyEditorManager::GetInstance();
	amyVariableEditor* w=em->GetDefaultEditor(v.GetType());
	if(w)
	{
		w->SetInput(v);
		w->show();
		this->repaint();
	}
	else
	{
		w=new amyVariableEditor(this);
		w->SetInput(v);
		w->show();
	}
}
//void QAMYCuisineWindow::ContextVariableViewMenu(QPoint p)
//{
//	QCursor cur=this->cursor();
//	QMenu* menu=new QMenu(this);
//	
//	amyEditorManager* em=amyEditorManager::GetInstance();
//	vector<amyVariableItem*> larr;
//	this->m_VariableArea->GetSelectedItemArr(larr);
//	qSort(larr.begin(),larr.end(),ItemCompareLeft2Right);
//	vector<amyVariable> vararr;
//	for(int i=0;i<larr.size();i++)
//	{
//		vararr.push_back(larr[i]->GetInput());
//	}
//	QMenu* openwithmenu=em->GetEditorMenu(vararr,menu);
//	if(openwithmenu)
//		menu->addMenu(openwithmenu);
//	{
//		QAction* act=new QAction("Delete them",this);
//		connect(act,SIGNAL(triggered()),m_VariableArea,SLOT(DeleteSelected()));
//		menu->addAction(act);
//	}
//	{
//		QAction* act=new QAction("Save them to folder",this);
//		connect(act,SIGNAL(triggered()),this,SLOT(SerializeSelected()));
//		menu->addAction(act);
//	}
//	{
//		QAction* act=new QAction("Load those in folder",this);
//		connect(act,SIGNAL(triggered()),this,SLOT(DeseraializeSelected()));
//		menu->addAction(act);
//	}
//	m_ContextMenuPos=p;
//	menu->exec(cur.pos());
//	delete menu;
//}
void QAMYCuisineWindow::contextVariableAreaMenuEvent(QContextMenuEvent *event)
{
	QCursor cur=this->cursor();
	QMenu* menu=new QMenu(this);
	
	amyEditorManager* em=amyEditorManager::GetInstance();
	vector<amyVariableItem*> larr;
	this->m_VariableArea->GetSelectedItemArr(larr);
	qSort(larr.begin(),larr.end(),ItemCompareLeft2Right);
	vector<amyVariable> vararr;
	for(int i=0;i<larr.size();i++)
	{
		vararr.push_back(larr[i]->GetInput());
	}
	QMenu* openwithmenu=em->GetEditorMenu(vararr,menu);
	if(openwithmenu)
		menu->addMenu(openwithmenu);
	{
		QAction* act=new QAction("Delete them",this);
		connect(act,SIGNAL(triggered()),m_VariableArea,SLOT(DeleteSelected()));
		menu->addAction(act);
	}
	{
		QAction* act=new QAction("Save them to folder",this);
		connect(act,SIGNAL(triggered()),this,SLOT(SerializeSelected()));
		menu->addAction(act);
	}
	{
		QAction* act=new QAction("Load those in folder",this);
		connect(act,SIGNAL(triggered()),this,SLOT(DeseraializeSelected()));
		menu->addAction(act);
	}
	m_ContextMenuPos=event->pos();
	menu->exec(cur.pos());
	delete menu;
}
#define SAVE_DIR "savedir"
void QAMYCuisineWindow::SerializeSelected()
{
	amyVariableManager* tm=amyVariableManager::GetInstance();
	QSettings MySettings;
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),MySettings.value(SAVE_DIR).toString(),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if(dir=="")
		return;
	MySettings.setValue(SAVE_DIR,dir);
	vector<amyVariableItem*> lingarr;
	m_VariableArea->GetSelectedItemArr(lingarr);
	for(int i=0;i<lingarr.size();i++)
	{

		if(0==tm->Serialize(dir,lingarr[i]->GetInput()))
		{
			continue;
		}
	}
}
void QAMYCuisineWindow::DeseraializeSelected()
{
	QSettings MySettings;
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),MySettings.value(SAVE_DIR).toString(),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if(dir=="")
		return;
	MySettings.setValue(SAVE_DIR,dir);
	amyVariableManager* tm=amyVariableManager::GetInstance();
	vector<amyVariable> varr;
	tm->Deserialize(dir,varr);

	QAction* act=qobject_cast<QAction* >(this->sender());
	QMenu* menu=act->menu();
	QPoint pos=m_ContextMenuPos;
	int x=pos.x();
	int y=pos.y();
	//amyCube::tCube::Pointer ob=varr[0].Get<amyCube>()->obj;
	for(int i=0;i<varr.size();i++)
	{
		m_VariableArea->AddVariable(varr[i],x,y);
		x+=80;
	}
}

void QAMYCuisineWindow::BeginProgress()
{
	int m=pProgress->GetStepCount();
	m_ProgressBar->setMaximum(m-1);
	m_ProgressBar->setMinimum(0);
	m_ProgressBar->show();
}
void QAMYCuisineWindow::EndProgress()
{
	m_ProgressBar->hide();
}
void QAMYCuisineWindow::StepProgress(int a)
{
	m_ProgressBar->setValue(a);
	m_ProgressBar->update();
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	//update();
	//this->statusBar()->update();
}

//void QAMYCuisineWindow::InvalidInputNum()
//{
//	amyWarn("Error: Invalid Input Number");
//	m_StatusMessage->setText("Ready");
//	m_StatusMessage->repaint();
//}
//void QAMYCuisineWindow::InvalidInputType()
//{
//	amyWarn("Error: Invalid Input Variable Type");
//	m_StatusMessage->setText("Ready");
//	m_StatusMessage->repaint();
//}
//void QAMYCuisineWindow::InvalidOutputNum()
//{
//	amyWarn("Warning: Wrong Output Number");
//}
void QAMYCuisineWindow::AlgorithmBegin()
{
	m_StatusMessage->setText("Busy");
	m_StatusMessage->repaint();
}
void QAMYCuisineWindow::AlgorithmEnd()
{
	m_StatusMessage->setText("Ready");
	m_StatusMessage->repaint();
}

void QAMYCuisineWindow::InputCheckingBegin()
{
	m_StatusMessage->setText("Checking Input");
	m_StatusMessage->repaint();
}

void QAMYCuisineWindow::InputCheckingEnd()
{
	m_StatusMessage->setText("Checking Ready");
}