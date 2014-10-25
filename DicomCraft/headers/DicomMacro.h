#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_DICOMCRAFT)
		#define DICOM_INTERFACE _declspec(dllimport)
	#else
		#define DICOM_INTERFACE _declspec(dllexport)
	#endif
#else
	#define DICOM_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_DICOMCRAFT_TEMPLATE
	#define DICOMCRAFT_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define DICOMCRAFT_TEMPLATE_INTERFACE
#endif