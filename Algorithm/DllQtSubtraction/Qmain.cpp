#include"amyAlgorithm.h"
#include"amySubtractionAlgorithm.h"
#include"amyAlgorithmStack.h"
#include"itkImage.h"
#include"itkSubtractImageFilter.h"
#include"amyCube.h"
#include"Qmain.h"
#include<qmessagebox>
amyDLLSubtractionAlgorithm::amyDLLSubtractionAlgorithm(amyAlgorithmStack* input):amyAlgorithm(input)
{

}

void amyDLLSubtractionAlgorithm::Run()
{
	QCoreApplication* in=QApplication::instance();
	QWidget* m=new QWidget;
	m->show();
	QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	amyAlgorithmStack* stack=this->GetStack();
	amyVariable v1=stack->Pop();
	amyVariable v2=stack->Pop();
	if(v1.GetType()!=VTYPE_CUBE||v2.GetType()!=VTYPE_CUBE)
		return;
	amyCube* cube1=(amyCube*)v1.GetPtr();
	amyCube* cube2=(amyCube*)v2.GetPtr();

	typedef itk::SubtractImageFilter<amyCube::tCube> SubtractType;
	SubtractType::Pointer subtract=SubtractType::New();
	subtract->SetInput1(cube1->obj);
	subtract->SetInput2(cube2->obj);
	subtract->Update();
	amyVariable v3=amyVariable::New(VTYPE_CUBE,"Ret");
	amyCube* cube3=(amyCube*)v3.GetPtr();
	cube3->SetObj(subtract->GetOutput());
	stack->Push(v3);
}
amyAlgorithm*  GetAlgorithm(amyAlgorithmStack* input)
{
	return new amyDLLSubtractionAlgorithm(input);

}