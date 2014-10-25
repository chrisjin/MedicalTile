#pragma once
template<typename T>
class amyWrapper
{
public:
	amyWrapper(T& a){m_Obj=&a;}
	T& operator=(T a)
	{
		*m_Obj=a;
		return *m_Obj;
	}
private:
	T* m_Obj;
};