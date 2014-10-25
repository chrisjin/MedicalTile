#pragma once
#include"CoreEditorMacro.h"
#include"amyPure.h"
#include<QMap>
#include"amyTypes.h"
#include"amyVariable.h"
#include<vector>
#include<QObject>
using namespace std;
class amyEditorHive;
class amyVariableEditor;
class QMenu;
class QWidget;
class COREEDITOR_INTERFACE amyEditorManager:public QObject
{
	Q_OBJECT
public:
	amyEditorManager();
	void LoadCoreEditor();
	void GetEditorHiveArrByInputs(vector<amyVariable>& varr,vector<amyEditorHive*>& harr);
	amyVariableEditor* GetDefaultEditor(VTYPE v);
	QMenu* GetEditorMenu(vector<amyVariable>& varr,QWidget* p=0);
public slots:
	void    ReleaseInuptCache();
	void	BeforeExec();
private:
	QMap<QString,amyEditorHive*> m_Name2Hive;
	vector<amyEditorHive*>       m_HiveArr;
	QMap<VTYPE,amyEditorHive*>   m_DefaultType2Hive;
	vector<amyVariable>          m_InputCache;

	DEFINE_SINGLETON(amyEditorManager)
};