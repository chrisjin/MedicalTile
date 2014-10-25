#include"amyVariableItem.h"
#include<QPainter>
#include"amyVariableManager.h"
#include<QGraphicsScene>
#include"amyShuttle.h"
#define MARGINTOP 5
#define MARGINBOTTOM 20
#define LINGWIDTH   (64+MARGINTOP*2)
#define LINGHEIGHT  (64+MARGINTOP+MARGINBOTTOM)
#define THUMBWIDTH  (64)
#define THUMBHEIGHT (64)
amyVariableItem::amyVariableItem()
{

	m_Background=new QPixmap(LINGWIDTH,LINGHEIGHT);
	m_ActivatedBackground=new QPixmap(LINGWIDTH,LINGHEIGHT);
	QPainter p(m_Background);
	p.fillRect(QRect(0,0,LINGWIDTH,LINGHEIGHT),QColor(100,100,100));
	QPainter p1(m_ActivatedBackground);
	p1.fillRect(QRect(0,0,LINGWIDTH,LINGHEIGHT),QColor(255,255,0));
	this->setRect(QRect(0,0,LINGWIDTH,LINGHEIGHT));

	this->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
	m_Render=new QPixmap(LINGWIDTH,LINGHEIGHT);

	SetActivated(0);
}
void amyVariableItem::SetPosition(int x,int y)
{

}
void amyVariableItem::GetPosition(int& x,int &y)
{

}
void amyVariableItem::InitInput()
{
	if(this->GetInput().GetType()==VTYPE_NULL)
		return;
	amyVariableManager* tm=amyVariableManager::GetInstance();
	m_Thumb=tm->GetThumb(this->GetInput());
	m_PixThumb=QPixmap::fromImage(m_Thumb);
	VTYPE type=this->GetInput().GetType();
	string typestr=amyVariableManager::GetInstance()->GetTypeString(type);
	m_TypeText=QString("(")+typestr.c_str()+QString(")");
	UpdateRenderImage();
	update();
}
void amyVariableItem::UpdateRenderImage()
{
	VTYPE type=this->GetInput().GetType();
	if(type==VTYPE_NULL)
		return;
	QPainter painter(m_Render);
	QPixmap* todraw=this->IsActivated()?m_ActivatedBackground:m_Background;
	painter.drawPixmap(0,0,*todraw);
	painter.drawPixmap(QRect(MARGINTOP,MARGINTOP,THUMBWIDTH,THUMBHEIGHT),m_PixThumb);
}
void amyVariableItem::SetActivated(bool a)
{
	m_Activated=a;
	UpdateRenderImage();
	update();
}
QVariant amyVariableItem::itemChange ( GraphicsItemChange change, const QVariant & value )
{
	if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)
        {
           SetActivated(1);
        }
        else
        {
            SetActivated(0);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
void amyVariableItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget  )
{
		if(this->GetInput().GetType()==VTYPE_NULL)
		return;
	VTYPE type=this->GetInput().GetType();
	QRectF rect=this->rect();
	painter->drawPixmap(QRect(0,0,LINGWIDTH,LINGHEIGHT),*m_Render);
	painter->drawText(QRect(0,0+MARGINTOP+THUMBHEIGHT,rect.width(),MARGINBOTTOM),Qt::AlignCenter,
		QString("")+GetInput().GetName().c_str()+m_TypeText);
}


bool ItemCompareRight2Left(amyVariableItem* a1,amyVariableItem* a2)
{
	int x1,x2,d;
	QPointF p1=a1->pos();
	QPointF p2=a2->pos();
	return p1.x()>p2.x()?1:0;
}
bool ItemCompareLeft2Right(amyVariableItem* a1,amyVariableItem* a2)
{
	int x1,x2,d;
	QPointF p1=a1->pos();
	QPointF p2=a2->pos();
	return p1.x()<p2.x()?1:0;
}
