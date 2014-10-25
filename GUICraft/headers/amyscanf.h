#pragma once
#include"GuiMacro.h"
#include<QDialog>
class QTextEdit;
#include<vector>
#include<QFrame>
using namespace std;
class QLineEdit;
class QTableWidget;
namespace amyUtil
{
	class ScanfPatternDialog:public QDialog
	{
		Q_OBJECT
	public:
		ScanfPatternDialog(const char* str,QWidget *parent=0);
		void scanf(const char* fmt,...);
	public:
		vector<QLineEdit*> m_EditArr; 
		vector<char> argtype;
		vector<void*> acceptpointer;
	public slots:
		void OnOk();
	};

	class ScanfArrDialog:public QDialog
	{
		Q_OBJECT
	public:
		ScanfArrDialog(const char* str,vector<float>& arr,QWidget *parent=0);
	private:
		QTableWidget* m_Table;
		vector<float>& m_Arr;
	public slots:
		void OnOk();
	};
	GUI_INTERFACE QWidget* scanfpanel(QWidget* p,const char* fmt,...);
	GUI_INTERFACE void scanf(const char* fmt,...);
	GUI_INTERFACE void scanf(const char* prumpt,vector<float>& arr);
}