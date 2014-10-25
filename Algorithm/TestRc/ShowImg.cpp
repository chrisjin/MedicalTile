#include"ShowImg.h"
#include<QLabel>
#include<QDialog>
#include<QVBoxLayout>
#include<QGraphicsView>
#include<QGraphicsLineItem>
#include<QVector>
#include<QApplication>

DLL_IMPL_BEGIN(1)
	DLL_ALGO(ShowImg,0)
DLL_IMPL_END
class amyAxisItem:public QGraphicsItem
{
public:
	amyAxisItem()
	{
		m_MarginWidth=50;
	}
	void SetBound(float low,float high,float pos,Qt::Orientation o)
	{
		//this->setTransform(this->transform().rotate(-90));

		m_Low=low;
		m_High=high;
		m_Pos=pos;
		m_Orientation=o;
	}
	void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 )
	{
		//painter->drawText(boundingRect (),Qt::AlignCenter,"AAA");
		//painter->save();
		//painter->setMatrix(this->matrix());
		//painter->drawLine(-50,0,0,100);
		painter->drawLine(0,0,50,100);
		//painter->restore();
	}
	QRectF	boundingRect () const
	{
		QPointF p1;
		QPointF p2;
		if(m_Orientation==Qt::Vertical)
		{
			p1=QPointF(m_Pos-m_MarginWidth,m_Low);
			p2=QPointF(m_Pos,m_High);
		}
		else if(m_Orientation==Qt::Horizontal)
		{
			p1=QPointF(m_Low,m_Pos-m_MarginWidth);
			p2=QPointF(m_High,m_Pos);
		}
		return QRectF(p1,p2);
	}
private:
	float m_Low;
	float m_High;
	float m_Pos;
	Qt::Orientation m_Orientation;
	float m_MarginWidth;
};
#include"amyDoubleThresholdWidget.h"

class A
{
public:
	operator int()
	{
		return 1;
	}

};
void ShowImg::Run()
{
	A mm;
	int kk=mm;
	Wraper a;
	a.moveToThread(QCoreApplication::instance()->thread());
	a.func();
	this->PostError("KKKK");
	this->PostWarning("BBB");
}