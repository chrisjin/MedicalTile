//#include"amyMaskGenerator.h"
//#include"amyVariable.h"
//#include"amyAlgorithmStack.h"
//#include"amyCube.h"
//
//
//void amyMaskGenerator::Run()
//{
//	amyAlgorithmStack* stack=this->GetStack();
//	amyVariable v1=stack->Pop();
//	amyVariable v2=stack->Pop();
//	if(v1.GetType()!=VTYPE_CUBE||v2.GetType()!=VTYPE_CUBE)
//		return;
//
//	amyVariable v3=amyVariable::New(VTYPE_MASK,"Ret");
//	amyKeeper<amyMask> m;
//	m.Cast(v3.Get());
//	m->mask.Cast(v1.Get());
//	m->cube.Cast(v2.Get());
//
//	stack->Push(v3);
//}