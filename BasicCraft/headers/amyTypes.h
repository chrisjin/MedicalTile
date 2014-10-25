#pragma once
#include"amyPure.h"
#include<string>
using namespace std;
//enum VTYPE
//{
typedef int           VTYPE;
#define	VTYPE_NULL       (1)
#define	VTYPE_UNKNOWN    (2)
#define	VTYPE_CUBE       (3)
#define	VTYPE_SERIES_SET (4)
#define	VTYPE_SERIES     (5)
#define	VTYPE_GEO_LINE	 (6)
#define	VTYPE_FLOAT_ARR  (7)
#define	VTYPE_MASK       (8)
#define	VTYPE_FLOAT      (9)
#define	VTYPE_CUBE_ARR   (10)
#define	VTYPE_DATA_MATRIX     (11)
#define	VTYPE_POINT_ARR	 (12)
#define	VTYPE_DATA	     (13)
#define VTYPE_DATA_ARRAY      (14)
#define VTYPE_DATA_NUMBER  (15)
//};

//class amyTypeInfo:public amySingleton<amyTypeInfo>
//{
//public:
//	amyTypeInfo();
//private:
//	map<VTYPE>
//DEFINE_SINGLETON(amyTypeInfo)
//};