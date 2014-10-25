#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_COREEDITOR)
		#define COREEDITOR_INTERFACE _declspec(dllimport)
	#else
		#define COREEDITOR_INTERFACE _declspec(dllexport)
	#endif
#else
	#define COREEDITOR_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_COREEDITOR_TEMPLATE
	#define COREEDITOR_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define COREEDITOR_TEMPLATE_INTERFACE
#endif