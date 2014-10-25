#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_ALGOCRAFT)
		#define ALGOCRAFT_INTERFACE _declspec(dllimport)
	#else
		#define ALGOCRAFT_INTERFACE _declspec(dllexport)
	#endif
#else
	#define ALGOCRAFT_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_ALGOCRAFT_TEMPLATE
	#define ALGOCRAFT_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define ALGOCRAFT_TEMPLATE_INTERFACE
#endif


#define ISEQUAL(arg,num) (arg==num?1:0)



#define OUTPUT_NUM_SET(num)   bool CheckOutputNum(int n){return n==num?1:0;}
#define INPUT_NUM_SET(num)    bool CheckInputNum(int n){return n==num?1:0;}
#define OUTPUT_NUM_FREE       bool CheckOutputNum(int n){return 1;}
#define INPUT_NUM_FREE        bool CheckInputNum(int n){return 1;}

#define CHECK_NUM(a) if(a==0)return 0;
#define DEFINE_ALGO_CON(child,parent) child(amyAlgorithmBridge* input):parent(input){}
#define DEFAULT_ALGO_CON(child)  child(amyAlgorithmBridge* input):amyAlgorithm(input){}


#define DLL_DEFINE \
	extern "C"\
	{\
	_declspec(dllexport) int             GetAlgorithmNum();\
	_declspec(dllexport) amyAlgorithm*   GetAlgorithmByIndex(int index);\
	}

#define DLL_IMPL_BEGIN(num)\
	int GetAlgorithmNum()\
	{\
		return num;\
	}\
	amyAlgorithm*   GetAlgorithmByIndex(int index)\
	{
#define DLL_ALGO(name,i)\
		if(index==i)return new name;
#define DLL_IMPL_END\
		return 0;\
	}