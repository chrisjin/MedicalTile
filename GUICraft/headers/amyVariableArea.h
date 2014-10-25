#ifndef AMYVARIABLEAREA_H
#define AMYVARIABLEAREA_H

#include"amyCanvas.h"
#include<set>
#include<vector>
#include"amyVariable.h"
#include<QPoint>
#include<QRect>
#include"GuiMacro.h"
using namespace std;
class QDragEnterEvent;
class amyVariableLing;
class GUI_INTERFACE amyVariableArea : public amyCanvas
{
	Q_OBJECT

public:
	typedef set<amyVariableLing*>::iterator tIterator;
	amyVariableArea(QWidget *parent=0);
	~amyVariableArea();
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseLeaveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void leaveEvent ( QEvent * event );
	void contextMenuEvent(QContextMenuEvent *);

	void AddVariable(amyVariable v,int x,int y);
	void AddVariableArr(vector<amyVariable>& v,int x,int y);

	void GetSelectedLingArr(vector<amyVariableLing*>& lingarr);
	void GetSelectedVariableArr(vector<amyVariable>& vararr);
	void GetLingArrAt(int x,int y,vector<amyVariableLing*>& lingarr);
private:
	void UpdateLingSelection();
	void UpdateVariableSelection();
	vector<tIterator> &GetSelectedLing();
	set<amyVariableLing*> m_VariableLingSet;
	vector<tIterator> m_SelectedLingArr;
	vector<amyVariable>   m_SelectedVariable;
	bool m_BeginToSelect;
	QRect m_SelectionRect;
	QPoint m_BeginPoint;
	amyVariableLing* m_DragedLing;
	QPoint m_ContextMenuPos;
public slots:
	void DeleteSelected();
};

#endif // AMYVARIABLEAREA_H
