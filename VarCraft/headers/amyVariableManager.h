#pragma once
#include"VarMacro.h"
class QImage;
#include"amyVariable.h"
#include"amyTypes.h"
#include<map>
#include"amyPure.h"
#include<QMap>
#include<QWidget>
#include<vector>
using namespace std;
typedef QImage (*tThumbGenerator)(amyVariable);
class amyVariableEditor;
class amyVariableHive;
typedef amyVariableHive    VAR_HIVE;
typedef VAR_HIVE*          pVAR_HIVE;
#define HIVE(type) (amyVariableManager::GetInstance()->GetHive(type))
class VAR_INTERFACE amyVariableManager
{
	DEFINE_SINGLETON(amyVariableManager)
public:
	amyVariableManager();
	void               LoadVariableHive();
	QImage             GetThumb(amyVariable v);
	string             GetTypeString(VTYPE);
	amyVariableHive*   GetHive(VTYPE v);
	amyVariableHive*   GetHiveByString(QString name);
	bool               Serialize(QString path,amyVariable v);
	bool               Deserialize(QString path,vector<amyVariable>& v);

private:
	QMap<VTYPE,amyVariableEditor*> m_Editor;
	QMap<VTYPE,amyVariableHive*>   m_Type2Hive;
};