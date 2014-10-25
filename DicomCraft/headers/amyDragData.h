#pragma once
#include"amyPure.h"
#include"amyVariable.h"
#include"amyKeeper.h"
////Getdata之后不能delete 由setdata方管理
//class amyDragData:public amySingleton<amyDragData>
//{
//public:
//	void SetData(VTYPE type,amyKeeper<void> data,void* sender){m_Data=data;m_Type=type;m_Sender=sender;}
//	amyKeeper<void> GetData();
//	void* GetSender(){return m_Sender;}
//	VTYPE       GetType(){return m_Type;}
//	~amyDragData();
//private:
//	VTYPE             m_Type;
//	amyKeeper<void>  m_Data;
//	void*       m_Sender;
//};

//class amyDrag
//{
//	static void  SetData(VTYPE type,void* data);
//	static void* GetData();
//	static VTYPE GetType();
//};