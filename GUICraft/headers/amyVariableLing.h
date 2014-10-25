#pragma once
#include"amyDragableLing.h"
#include"amyVariable.h"
class amyCube;
class GUI_INTERFACE amyVariableLing:public amyRectDragableLing,public amyInput<amyVariable>
{
public:
	amyVariableLing(amyCanvas* can=0);
	void InitInput(); 
	void Render(QPaintDevice* dev); 
	void RenderThumb(QPaintDevice* dev);
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);

	virtual void mousePressEvent(QMouseEvent *event);
	void SetActivated(bool a);
	bool IsActivated(){return m_Activated;}
	QImage GetThumb(){return m_Thumb;}
	virtual void Update();
	~amyVariableLing();
private:
	QPixmap m_PixThumb;
	QImage  m_Thumb;
	QPixmap *m_Background;
	QPixmap *m_ActivatedBackground;
	bool m_Activated;
	QString m_TypeText;

	QPixmap *m_Render;
};

GUI_INTERFACE bool LingCompareRight2Left(amyVariableLing* a1,amyVariableLing* a2);
GUI_INTERFACE bool LingCompareLeft2Right(amyVariableLing* a1,amyVariableLing* a2);