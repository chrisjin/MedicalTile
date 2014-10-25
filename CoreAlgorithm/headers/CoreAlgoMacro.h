#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_COREALGO)
		#define COREALGO_INTERFACE _declspec(dllimport)
	#else
		#define COREALGO_INTERFACE _declspec(dllexport)
	#endif
#else
	#define COREALGO_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_COREALGO_TEMPLATE
	#define COREALGO_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define COREALGO_TEMPLATE_INTERFACE
#endif