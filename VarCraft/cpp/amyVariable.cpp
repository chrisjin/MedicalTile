#include"amyVariable.h"
#include"amyCube.h"
#include"amyGeo.h"
#include"amyDICOM.h"
#include"amyTypeWrap.h"
#include"amyVariableManager.h"
#include"amyVariableHive.h"
#define NAMELENGTH (255)
amyVariable amyVariable::New(VTYPE type,string name)
{
	amyVariable ret;
	pVAR_HIVE h=HIVE(type);
	if(h)
		ret = h->Produce(name);
	return ret; 
}
amyVariable amyVariable::New(amyKeeper<void> keeper,VTYPE type,string name)
{
	amyVariable v;
	v.m_Name=new char[NAMELENGTH];
	strcpy(v.m_Name.GetPointer(),"Nemo");
	v.m_Ptr=keeper;
	v.m_Type=type;
	return v;
}
amyVariable::amyVariable()
{
	m_Type=VTYPE_NULL;
	m_Name=new char[NAMELENGTH];
	m_Name.GetPointer()[0]='\0';
	strcpy(m_Name.GetPointer(),"Nemo");
}

amyVariable::amyVariable(VTYPE type,string name,amyKeeper<void> data)
{
    m_Type=type;
    m_Ptr=data;
	m_Name=new char[NAMELENGTH];
	strcpy(m_Name.GetPointer(),name.c_str());       
}

void  amyVariable::SetName(string name)
{
	strcpy(m_Name.GetPointer(),name.c_str());
}
bool amyVariable::IsValid()
{
	if(this->GetType()==VTYPE_NULL||m_Ptr.IsNull())
		return 0;
	else
		return 1;
}

