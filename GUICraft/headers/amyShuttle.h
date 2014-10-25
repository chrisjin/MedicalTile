#pragma once
#include"amyPure.h"
#include"amyKeeper.h"
#include"amyTypes.h"
#include<QWidget>
#include"GuiMacro.h"
//class SpecialMimeData:public QMimeData
//{
//public:
//
//};
class GUI_INTERFACE amyShuttle
{
	DEFINE_SINGLETON(amyShuttle)
public:
	amyShuttle();
	void SendData(VTYPE type,amyKeeper<void> data,QWidget* sender);
	void SendData(VTYPE type,amyKeeper<void> data,QPixmap pix,QWidget* sender);
	amyKeeper<void> GetData();
	void SetData(VTYPE type,amyKeeper<void> data,QWidget* sender);
	void ClearData();
	void* GetSender(){return m_Sender;}
	VTYPE       GetType(){return m_Type;}
private:
	VTYPE             m_Type;
	amyKeeper<void>  m_Data;
	QWidget*       m_Sender;
};