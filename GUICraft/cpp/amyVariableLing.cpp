#include"amyVariableLing.h"
#include<QPainter>
#include"amyQUtil.h"
#include"amyVariableManager.h"
#define MARGINTOP 5
#define MARGINBOTTOM 20
#define LINGWIDTH   (64+MARGINTOP*2)
#define LINGHEIGHT  (64+MARGINTOP+MARGINBOTTOM)
#define THUMBWIDTH  (64)
#define THUMBHEIGHT (64)
amyVariableLing::amyVariableLing(amyCanvas* can):amyRectDragableLing(can)
{
	m_Background=new QPixmap(LINGWIDTH,LINGHEIGHT);
	m_ActivatedBackground=new QPixmap(LINGWIDTH,LINGHEIGHT);
	QPainter p(m_Background);
	p.fillRect(QRect(0,0,LINGWIDTH,LINGHEIGHT),QColor(100,100,100));
	QPainter p1(m_ActivatedBackground);
	p1.fillRect(QRect(0,0,LINGWIDTH,LINGHEIGHT),QColor(255,255,0));
	SetActivated(0);
	this->SetRect(amyRect(0,0,LINGWIDTH,LINGHEIGHT));

	m_Render=new QPixmap(LINGWIDTH,LINGHEIGHT);
}
amyVariableLing::~amyVariableLing()
{
	
	delete m_Background;
	delete m_ActivatedBackground;
	delete  m_Render;
}
void amyVariableLing::Update()
{
	VTYPE type=this->GetInput().GetType();
	if(type==VTYPE_NULL)
		return;
	QPainter painter(m_Render);
	amyRect rect=this->GetRect();
	string typestr=amyVariableManager::GetInstance()->GetTypeString(type);
	QPixmap* todraw=this->IsActivated()?m_ActivatedBackground:m_Background;
	painter.drawPixmap(0,0,*todraw);
	painter.drawPixmap(QRect(MARGINTOP,MARGINTOP,THUMBWIDTH,THUMBHEIGHT),m_PixThumb);
}
void amyVariableLing::InitInput()
{
	this->GetCanvas()->setAcceptDrops(true);
	
	if(this->GetInput().GetType()==VTYPE_NULL)
		return;
	amyVariableManager* tm=amyVariableManager::GetInstance();
	m_Thumb=tm->GetThumb(this->GetInput());
	m_PixThumb=QPixmap::fromImage(m_Thumb);
	VTYPE type=this->GetInput().GetType();
	string typestr=amyVariableManager::GetInstance()->GetTypeString(type);
	m_TypeText=QString("(")+typestr.c_str()+QString(")");

	Update();
}
void amyVariableLing::SetActivated(bool a)
{
	m_Activated=a;
	Update();
	this->GetCanvas()->repaint();
}

void amyVariableLing::Render(QPaintDevice* dev)
{
	if(this->GetInput().GetType()==VTYPE_NULL)
		return;
	VTYPE type=this->GetInput().GetType();
	QPainter painter(dev);
	amyRect rect=this->GetRect();
	painter.drawPixmap(QRect(rect.x,rect.y,LINGWIDTH,LINGHEIGHT),*m_Render);
	////switch(type)
	////{
	////case VTYPE_CUBE:
	////case VTYPE_SERIES_SET:
	//	RenderThumb(dev);
	////	break;
	////
	////}
	//QPainter painter(dev);
	//
	//string typestr=amyVariableManager::GetInstance()->GetTypeString(type);
	//painter.drawText(QRect(rect.x,rect.y+MARGINTOP+THUMBHEIGHT,rect.width,MARGINBOTTOM),Qt::AlignCenter,
	//	QString("")+GetInput().GetName().c_str()+m_TypeText);
	painter.drawText(QRect(rect.x,rect.y+MARGINTOP+THUMBHEIGHT,rect.width,MARGINBOTTOM),Qt::AlignCenter,
		QString("")+GetInput().GetName().c_str()+m_TypeText);
}
void amyVariableLing::RenderThumb(QPaintDevice* dev)
{
	QPainter painter(dev);
	amyRect rect=this->GetRect();

	QPixmap* todraw=this->IsActivated()?m_ActivatedBackground:m_Background;
	painter.drawPixmap(QRect(rect.x,rect.y,LINGWIDTH,LINGHEIGHT),*todraw);
	painter.drawPixmap(QRect(rect.x+MARGINTOP,rect.y+MARGINTOP,THUMBWIDTH,THUMBHEIGHT),m_PixThumb);
}

void amyVariableLing::dropEvent(QDropEvent *event)
{

}
void amyVariableLing::dragEnterEvent(QDragEnterEvent *event)
{
	 event->acceptProposedAction();
}

void amyVariableLing::mousePressEvent(QMouseEvent *event)
{
	if(this->IsContain(event->x(),event->y()))
	{
		//this->SetActivated(1);
	}
	else
	{
		//this->SetActivated(0);
	}
	amyDragableLing::mousePressEvent(event);
}


bool LingCompareRight2Left(amyVariableLing* a1,amyVariableLing* a2)
{
	int x1,x2,d;
	a1->GetPosition(x1,d);
	a2->GetPosition(x2,d);
	return x1>x2?1:0;
}

bool LingCompareLeft2Right(amyVariableLing* a1,amyVariableLing* a2)
{
	int x1,x2,d;
	a1->GetPosition(x1,d);
	a2->GetPosition(x2,d);
	return x1<x2?1:0;
}