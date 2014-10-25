#ifndef AMYVARIABLEEDITOR_H
#define AMYVARIABLEEDITOR_H
#include"EditorMacro.h"
#include <QDialog>
#include"amyPure.h"
#include"amyVariable.h"
#include<vector>
#include<string>
#include<QImage>
#include"amyVariableHive.h"
using namespace std;
class QVBoxLayout;
class QLineEdit;
class EDITOR_INTERFACE amyVariableEditor : public QDialog
{
	Q_OBJECT

public:
	amyVariableEditor(QWidget *parent=0);
	virtual					~amyVariableEditor();
	virtual void			InitInput(); 
	QVBoxLayout*			GetMainLayout(){return m_Layout;}
	QWidget*				GetMainWidget(){return m_Widget;}
	virtual void			closeEvent ( QCloseEvent * event );						
	virtual void			Confirm();
	virtual void			Cancel();
	void					SetInput(amyVariable v);
	void					SetInputArr(vector<amyVariable>& varr);
	amyVariable				GetInput();
	vector<amyVariable>&	GetInputArr();
signals:
	void s_confirm();
	void s_cancel();
	void s_close();
public slots:
	void SlotConfirm();
	void SlotCancel();
private:
	vector<amyVariable> m_InputArr;
	QWidget    *m_Widget;
	QVBoxLayout* m_Layout;
	QLineEdit  * m_NameEdit;
};

#endif // AMYVARIABLEEDITOR_H
