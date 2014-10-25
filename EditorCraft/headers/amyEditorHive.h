#pragma once
#include"EditorMacro.h"
#include<QIcon>
#include"amyVariable.h"
#include<QObject>
class amyVariableEditor;
class EDITOR_INTERFACE amyEditorHive:public QObject
{
	Q_OBJECT
public:
	virtual amyVariableEditor* Produce()=0;
	virtual QIcon              GetIcon();
	virtual const char*        GetName()=0;
	virtual bool               CheckInputNum(int num)=0;
	virtual bool			   CheckInputArgument(int index,amyVariable v)=0;
signals:
	void	s_retrieve();
};