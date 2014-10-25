//#pragma once
//
//template<typename T>
//void* ConstructFuncWithType()
//{
//	return new T;
//}
//
//class amyConstructor
//{
//public:
//	typedef void* (*ConstructFunc)();
//	
//	template<typename T>
//	amyConstructor()
//	{
//		m_ConstructFunc=All_Cast<ConstructFuncWithType<T>,ConstructFunc>();
//	}
//	template<typename T>
//	T* Do()
//	{
//		return (T*)m_ConstructFunc();
//	}
//private:
//	ConstructFunc m_ConstructFunc;
//};