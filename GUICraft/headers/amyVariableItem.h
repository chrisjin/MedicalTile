#pragma once
#include"GuiMacro.h"
#include<QGraphicsRectItem>
#include"amyVariable.h"
#include"amyPure.h"
#include<QPixmap>
#include<QString>
#include<QObject>
class GUI_INTERFACE amyVariableItem:public QObject,public QGraphicsRectItem,public amyInput<amyVariable>
{
	Q_OBJECT
public:
	amyVariableItem();
	void InitInput(); 
	void SetActivated(bool a);
	void SetPosition(int x,int y);
	void GetPosition(int& x,int &y);
	bool IsActivated(){return m_Activated;}
	QImage GetThumb(){return m_Thumb;}
	void UpdateRenderImage();
	virtual QVariant	itemChange ( GraphicsItemChange change, const QVariant & value );
	void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
signals:
	void s_moveoutside();
private:
	QPixmap m_PixThumb;
	QImage  m_Thumb;
	QPixmap *m_Background;
	QPixmap *m_ActivatedBackground;
	bool m_Activated;
	QString m_TypeText;

	QPixmap *m_Render;
};

GUI_INTERFACE bool ItemCompareRight2Left(amyVariableItem* a1,amyVariableItem* a2);
GUI_INTERFACE bool ItemCompareLeft2Right(amyVariableItem* a1,amyVariableItem* a2);