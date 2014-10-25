#include"amyAlgorithm.h"
#include"amyAlgorithmBridge.h"
#include"amyAlgorithmStack.h"
#include"amyAlgorithmPanel.h"
#include"amyAlgorithmMessager.h"
amyAlgorithm::amyAlgorithm()
{
}
amyAlgorithmStack* amyAlgorithm::GetStack()
{
	return amyAlgorithmStack::GetInstance();
}

QFrame* amyAlgorithm::CreatePanel(QWidget* parent)
{
	return new amyAlgorithmPanel(this,parent);
}

void amyAlgorithm::PostWarning(const char* info)
{
	amyAlgorithmMessager::GetInstance()->PostWarning(this,info);
}
void amyAlgorithm::PostError(const char* info)
{
	amyAlgorithmMessager::GetInstance()->PostError(this,info);
}
