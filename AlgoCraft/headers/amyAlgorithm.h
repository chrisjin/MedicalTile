#pragma once
#include"AlgoMacro.h"
#include"amyTypes.h"
#include<vector>
#include"amyVariable.h"
class amyAlgorithmBridge;
class amyAlgorithmStack;
class QFrame;
class QIcon;
class amyAlgorithmInfo;
class QWidget;
class amyAlgorithmPanel;
class ALGOCRAFT_INTERFACE amyAlgorithm
{
public:
	amyAlgorithm();
	virtual bool			  CheckInputArr(std::vector<amyVariable>& arr)=0;
	virtual const char*       GetAlgorithmName()=0;
	virtual void			  Run()=0;
	
	void                      PostWarning(const char* info);
	void                      PostError(const char* info);

	virtual const char*	      GetCategory(){return "Algorithm";}


	virtual string			  GetAuthor(){return "";}
	virtual string            GetHint(){return "";}
	virtual string            GetDescription(){return "";}

	virtual QFrame*           CreatePanel(QWidget* parent);
	virtual QIcon*            GetIcon(){return 0;}


	amyAlgorithmStack*        GetStack();
};



