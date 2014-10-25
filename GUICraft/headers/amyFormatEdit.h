#pragma once
#include"GuiMacro.h"
#include<QFrame>
#include<vector>
using namespace std;
class QLineEdit;
class GUI_INTERFACE amyFormatEdit:public QFrame
{
public:
	amyFormatEdit(QWidget *parent=0);
	void scanf(const char* fmt,...);
	void Update();
public:
	vector<QLineEdit*> m_EditArr; 
	vector<char> argtype;
	vector<void*> acceptpointer;
};