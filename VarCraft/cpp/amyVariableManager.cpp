#include"amyVariableManager.h"
#include<QImage>
//#include"amyQUtil.h"
//#include"amyVariableEditor.h"
//#include"amyMaskEditor.h"
#include"amyCube.h"
//#include"amyCubeEditor.h"
//#include"amyFloatArrEditor.h"
#include"amyTypeWrap.h"
#include"amySerialize.h"
#include<qfiledialog>
//#include"amyPointArrEditor.h"
#include"amyCubeHive.h"
#include"amyMatrixHive.h"
#include"amyArrayHive.h"
#include"amySeriesSetHive.h"
#include"amyNumberHive.h"
IMPLEMENT_SINGLETON(amyVariableManager)
void amyVariableManager::LoadVariableHive()
{
#define LOAD_HIVE(type)\
	{\
	amyVariableHive* h=new amy##type##Hive;\
		this->m_Type2Hive.insert(h->GetType(),h);\
	}
	LOAD_HIVE(Cube);
	//LOAD_HIVE(Data);
	LOAD_HIVE(Matrix);
	LOAD_HIVE(Array);
	LOAD_HIVE(SeriesSet);
	LOAD_HIVE(Number);
}
amyVariableManager::amyVariableManager()
{
	LoadVariableHive();
}
amyVariableHive*   amyVariableManager::GetHive(VTYPE v)
{
	if(m_Type2Hive.find(v)==m_Type2Hive.end())
		return 0;
	else
		return m_Type2Hive[v];
}
amyVariableHive*   amyVariableManager::GetHiveByString(QString name)
{
	QMap<VTYPE,amyVariableHive*>::Iterator itr=m_Type2Hive.begin();
	for(;itr!=m_Type2Hive.end();++itr)
	{
		if(itr.value()->GetString()==name)
			return itr.value();
	}
	return 0;
}
QImage amyVariableManager::GetThumb(amyVariable v)
{
	pVAR_HIVE h=HIVE(v.GetType());
	if(h)
		return h->GetIcon(v);
	return QImage();
}
string amyVariableManager::GetTypeString(VTYPE v)
{
	pVAR_HIVE h=HIVE(v);
	if(h)
		return h->GetString();
	else
		return "";
}

bool amyVariableManager::Serialize(QString path,amyVariable v)
{
	return amySerialize::Variable(path,v);
}

bool amyVariableManager::Deserialize(QString path,vector<amyVariable>& varr)
{
	return amyDeserialize::Variable(path,varr);
}