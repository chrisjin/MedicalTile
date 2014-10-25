#include"amyMatrix.h"

amyMatrix::~amyMatrix()
{
}
amyArray& amyMatrix::addrow()
{
	amyArray* a=new amyArray;
	this->m_Data.push_back(a);
	return *a;
}
void amyMatrix::addrow(int num)
{
	for(int i=0;i<num;i++)
	{
		this->m_Data.push_back(new amyArray);
	}
}
amyArray& amyMatrix::operator[](int index)
{
	return *m_Data[index].GetPointer();
}

int amyMatrix::rowcount()
{
	return m_Data.size();
}

vector<amyKeeper<amyArray>>& amyMatrix::operator()()
{
	return m_Data;
}