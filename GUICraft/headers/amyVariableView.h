#pragma once
#include<QGraphicsView>
#include<set>
#include<vector>
#include"amyVariable.h"
#include<QPoint>
#include<QRect>
#include"GuiMacro.h"
#include<QGraphicsItem>
#include<QString>
#include"amyVariableItem.h"
using namespace std;
class QDragEnterEvent;
class amyVariableLing;
class QGraphicsScene;
class QGraphicsSceneContextMenuEvent;
class QGraphicsSceneMouseEvent;
class amyVariableScene:public QGraphicsScene
{
	Q_OBJECT
public:
	amyVariableScene(QObject* p=0):QGraphicsScene(p){}
	//void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
signals:
	//void s_contextmenu(QPointF);
};



class GUI_INTERFACE amyVariableView : public QGraphicsView
{
	Q_OBJECT

public:
	//typedef set<amyVariableLing*>::iterator tIterator;
	amyVariableView(QWidget *parent=0);
	~amyVariableView();
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void mouseViewportMoveEvent(QMouseEvent *event);
	//void contextMenuEvent(QContextMenuEvent *);
	bool eventFilter(QObject *obj, QEvent *event);
	void AddVariable(amyVariable v,int x,int y);
	void AddVariableArr(vector<amyVariable>& v,int x,int y);
	void GetSelectedItemArr(vector<amyVariableItem*>& lingarr);
	amyVariableItem* GetItemAt(int x,int y);
	void GetItemArrAt(int x,int y,vector<amyVariableItem*>& lingarr);
	void GetItemPosition(amyVariableItem* item,int& x,int& y);
	QGraphicsScene* GetScene(){return m_Scene;}
	//void GetSelectedLingArr(vector<amyVariableLing*>& lingarr);
	//void GetSelectedVariableArr(vector<amyVariable>& vararr);
	//void GetLingArrAt(int x,int y,vector<amyVariableLing*>& lingarr);
signals:
	void s_contextmenu(QPoint);
private:
	QGraphicsScene* m_Scene;
	QPoint m_ContextMenuPos;
public slots:
	void DeleteSelected();
	//void ContextSceneMenu(QPointF);
};

