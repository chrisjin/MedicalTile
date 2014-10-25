#ifndef AMYMASKEDITOR_H
#define AMYMASKEDITOR_H
#include"CoreEditorMacro.h"
#include "amyVariableEditor.h"
#include "amyCanvas.h"
#include<qscrollarea>
#include<QListWidget>
#include"amyEditorHive.h"
class amyMaskLing;
class QScrollBar;
class COREEDITOR_INTERFACE amyMaskWidget:public QWidget
{
	Q_OBJECT
public:
	amyMaskWidget(QWidget *parent=0);
	amyMaskLing* m_MaskLing;
	amyCanvas*   m_Canvas;
	QScrollBar *m_TanspSlider;
	void mouseMoveEvent(QMouseEvent * event);
public slots:
	void SetTransp(int a);
};

class COREEDITOR_INTERFACE EraseChoosePanel:public QListWidget
{
public:
	EraseChoosePanel(QWidget* parent=0);
};
class COREEDITOR_INTERFACE ToolPanel:public QWidget
{
	Q_OBJECT
public:
	ToolPanel(QWidget *parent=0);
signals:
	void s_erase();
	void s_grow();
	void s_growinslice();
	void s_removeothers();
	void s_removethis();
	void s_noedit();
	void s_draw();
	void s_erasesize(int);
};

class amyCube;
class COREEDITOR_INTERFACE amyMaskEditor : public amyVariableEditor
{
	Q_OBJECT

public:
	enum eMode
	{
		EDIT_DRAW,
		EDIT_ERASE,
		EDIT_GROW,
		EDIT_GROWINSLICE,
		EDIT_NOEDIT
	};
	amyMaskEditor(QWidget *parent=0);
	~amyMaskEditor();
	void InitInput();
	void DoEraseOrDraw(QMouseEvent * event,bool iserase);
	void DoGrow(QMouseEvent * event);
	void DoGrowInSlice(QMouseEvent * event);
	bool eventFilter(QObject *target, QEvent *event);
	void mouseCanvasMoveEvent(QMouseEvent * event);
	void mouseCanvasPressEvent(QMouseEvent * event);
	void Confirm();
	void Grow3D(int x,int y);
	void Grow2D(int x,int y);
	const char* GetName(){return "Mask Editor";}
public slots:
	void SetMode(eMode m);
	void SetGrow();
	void SetErase();
	void SetEraseSize(int);
	void SetDraw();
	void SetNoEdit();
	void SetGrowInSlice();
	void RemoveOtherSlice();
	void RemoveThisSlice();
private:
	eMode m_Mode;
	amyMaskWidget    * m_MainWidget;
	int  m_EraseSize;
	amyCube *m_InnerMask;
	
};
class amyMaskEditorHive:public amyEditorHive
{
public:
	amyVariableEditor* Produce(){return new amyMaskEditor;}
	const char*        GetName(){return "amyMaskEditor";}
	virtual bool               CheckInputNum(int num)
	{
		if(num==2)
			return 1;
		else return 0;
	}
	virtual bool			   CheckInputArgument(int index,amyVariable v)
	{
		if(v.GetType()==VTYPE_CUBE)
			return 1;
		else
			return 0;
	};
	QIcon   GetIcon();
};
#endif // AMYMASKEDITOR_H
