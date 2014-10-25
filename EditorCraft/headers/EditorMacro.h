#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_EDITORCRAFT)
		#define EDITOR_INTERFACE _declspec(dllimport)
	#else
		#define EDITOR_INTERFACE _declspec(dllexport)
	#endif
#else
	#define EDITOR_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_EDITORCRAFT_TEMPLATE
	#define EDITORCRAFT_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define EDITORCRAFT_TEMPLATE_INTERFACE
#endif