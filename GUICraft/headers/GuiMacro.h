#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_GUICRAFT)
		#define GUI_INTERFACE _declspec(dllimport)
	#else
		#define GUI_INTERFACE _declspec(dllexport)
	#endif
#else
	#define GUI_INTERFACE _declspec(dllimport)
#endif