
#ifdef _WINDLL
	#if defined(IMPORT_MATH)
		#define MATH_INTERFACE _declspec(dllimport)
	#else
		#define MATH_INTERFACE _declspec(dllexport)
	#endif
#else
	#define MATH_INTERFACE _declspec(dllimport)
#endif

