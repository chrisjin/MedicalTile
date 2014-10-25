#pragma once
#include"GuiMacro.h"
#include<QImage>
class amySeries;
class amyCube;
class amyFloat;
class amyCubeArr;
namespace amyUtil
{
//GUI_INTERFACE QImage* GetSeriesThumb(amySeries* ser);

GUI_INTERFACE QImage GetCubeThumb(amyCube* cube);

//GUI_INTERFACE QImage GetFloatThumb(amyFloat* num);

//GUI_INTERFACE QImage GetCubeArrThumb(amyCubeArr* cubearr);
}