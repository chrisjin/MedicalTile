#include"amyCubeEditor.h"
#include<QVBOXLayout>
#include"amyCube.h"
#include"amyDICOM.h"
#include"amyGroupLing.h"
#include"amyMeasureLing.h"
amyCubeEditor::amyCubeEditor(QWidget *parent)
	: amyVariableEditor(parent)
{

	amyCanvas *c=new amyCanvas(this);
	m_CubLing=new amyCubeLing(c);

	m_CubLing->SetInput(0);
	QVBoxLayout* l=new QVBoxLayout(this);
	QWidget* w=this->GetMainWidget();
	w->setLayout(l);
	l->addWidget(c);
}
void amyCubeEditor::InitInput()
{
	amyVariable v=GetInput();
	if(v.GetType()!=VTYPE_CUBE)
		return;
	amyCube::Keeper cube=v.Get<amyCube>();
	m_CubLing->SetInput(cube.GetPointer());
	this->resize(512,512);
	repaint();
	amyVariableEditor::InitInput();
}

QIcon   amyCubeEditorHive::GetIcon()
{
	QIcon i=QIcon(":/ICON/CubeViewer");

	//i.res
	return i;
}