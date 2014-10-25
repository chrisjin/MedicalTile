#pragma once
#include"GuiMacro.h"
#include"amyPure.h"
#include<QDialog>
class QProgressBar;
#define pProgressBar (amyProgressBar::GetInstance())
class GUI_INTERFACE amyProgressBar:public QDialog
{
	DEFINE_SINGLETON(amyProgressBar)
public:
	amyProgressBar();
	void SetRange(int a,int b);
	void SetValue(int c);
private:
	QProgressBar* m_Bar;
};