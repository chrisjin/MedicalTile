#pragma once
#include"CoreEditorMacro.h"
#include"amyPure.h"
#include<QWidget>
class amyMatrix;
class COREEDITOR_INTERFACE amyMatrixWidget:public QWidget,public amyInput<amyMatrix*>
{

};