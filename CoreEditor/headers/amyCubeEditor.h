#pragma once
#include"CoreEditorMacro.h"
#include"amyVariableEditor.h"
#include"amyROILing.h"
#include"amyEditorHive.h"
class amyMeasureLing;
class amyCubeLing;

class COREEDITOR_INTERFACE amyCubeEditor:public amyVariableEditor
{
public:
	amyCubeEditor(QWidget *parent=0);
	~amyCubeEditor(){}
	void InitInput();
private:
	amyCubeLing* m_CubLing;
	amyMeasureLing* m_MeasureLing;
};



class amyCubeEditorHive:public amyEditorHive
{
public:
	amyVariableEditor* Produce(){return new amyCubeEditor;}
	const char*        GetName(){return "Cube Viewer";}
	virtual bool               CheckInputNum(int num)
	{
		if(num==1)
			return 1;
		else return 0;
	}
	virtual bool			   CheckInputArgument(int index,amyVariable v)
	{
		if(v.GetType()==VTYPE_CUBE)
			return 1;
		else
			return 0;
	};
	QIcon   GetIcon();
};