#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_BASICCRAFT)
		#define BASIC_INTERFACE _declspec(dllimport)
	#else
		#define BASIC_INTERFACE _declspec(dllexport)
	#endif
#else
	#define BASIC_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_BASICCRAFT_TEMPLATE
	#define BASICCRAFT_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define BASICCRAFT_TEMPLATE_INTERFACE
#endif