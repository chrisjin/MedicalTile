#include"amyArray.h"
amyArray::~amyArray()
{
	m_Data;
}
int amyArray::size()
{
	return m_Data.size();
}
float& amyArray::at(int i)
{
	return m_Data[i];
}
float& amyArray::operator[](int i)
{
	return m_Data[i];
}

amyArray::tData& amyArray::operator()()
{
	return m_Data;
}