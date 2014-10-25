#include"amyEditorManager.h"
#include"amyCubeEditor.h"
#include"amyEditorHive.h"
#include"amyMaskEditor.h"
#include<QMenu>
#include<QPlastiqueStyle>
#include"amyDataEditor.h"
#include"amySeriesSetEditor.h"
IMPLEMENT_SINGLETON(amyEditorManager)
amyEditorManager::amyEditorManager()
{
	LoadCoreEditor();
}

void amyEditorManager::LoadCoreEditor()
{
#define LOAD_EDITOR(name)\
	{\
		amy##name##EditorHive* h=new amy##name##EditorHive;\
		m_Name2Hive.insert(h->GetName(),h);\
		m_HiveArr.push_back(h);

	LOAD_EDITOR(Cube)
		m_DefaultType2Hive.insert(VTYPE_CUBE,h);
	}
	LOAD_EDITOR(Mask)
	}
	LOAD_EDITOR(Data)
		m_DefaultType2Hive.insert(VTYPE_DATA_ARRAY,h);
		m_DefaultType2Hive.insert(VTYPE_DATA_MATRIX,h);
	}
	LOAD_EDITOR(SeriesSet)
		m_DefaultType2Hive.insert(VTYPE_SERIES_SET,h);
	}

}

void amyEditorManager::GetEditorHiveArrByInputs(vector<amyVariable>& varr,vector<amyEditorHive*>& harr)
{
	for(int j=0;j<m_HiveArr.size();j++)
	{
		bool flag=1;
		flag=m_HiveArr[j]->CheckInputNum(varr.size());
		if(flag)
		{
			for(int i=0;i<varr.size();i++)
			{
				flag=m_HiveArr[j]->CheckInputArgument(i,varr[i]);
				if(flag==0)
					break;
			}
		}
		if(flag==1)
			harr.push_back(m_HiveArr[j]);
	}
}

amyVariableEditor* amyEditorManager::GetDefaultEditor(VTYPE v)
{
	if(m_DefaultType2Hive.find(v)!=m_DefaultType2Hive.end())
	{
		return m_DefaultType2Hive[v]->Produce();
	}
	else
		return 0;
}
class QTMyIconStyle : public QPlastiqueStyle  
{   
public:  
	QTMyIconStyle (){}
	virtual ~QTMyIconStyle (){}
	virtual int pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
	{  
		int s = QPlastiqueStyle::pixelMetric(metric, option, widget);  
		if (metric == QStyle::PM_SmallIconSize) {  
			s = 50;  
		}  
		return s;  
	}  
};  

QMenu* amyEditorManager::GetEditorMenu(vector<amyVariable>& varr,QWidget* p)
{
	if(varr.size()==0)
		return 0;
	vector<amyEditorHive*> ha;
	GetEditorHiveArrByInputs(varr,ha);
	if(ha.size()==0)
		return 0;
	QMenu* m=new QMenu("Open With",p);
	m->setStyle(new QTMyIconStyle);
	m_InputCache=varr;
	connect(m,SIGNAL(destroyed()),this,SLOT(ReleaseInuptCache()));
	for(int i=0;i<ha.size();i++)
	{
		QAction* action=new QAction(ha[i]->GetIcon(),ha[i]->GetName(),p);
		m->addAction(action);
		connect(action,SIGNAL(triggered()),ha[i],SIGNAL(s_retrieve()),Qt::UniqueConnection);
		connect(ha[i],SIGNAL(s_retrieve()),this,SLOT(BeforeExec()),Qt::UniqueConnection);
	}
	return m;
}
void amyEditorManager::BeforeExec()
{
	amyEditorHive* eh=qobject_cast<amyEditorHive*>(this->sender());
	amyVariableEditor* e=eh->Produce();
	if(e)
	{
		e->SetInputArr(m_InputCache);
		e->show();
	}
}
void amyEditorManager::ReleaseInuptCache()
{
	m_InputCache.clear();
}
