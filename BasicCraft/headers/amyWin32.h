#pragma once
#include"BasicMacro.h"
class BASIC_INTERFACE amyFolder
{
public:
	void Open(const char* name,bool isiter=1);
	virtual void OnFindFile(const char* name);


};


