#include"amyNumber.h"

amyNumber::amyNumber()
{

}
amyNumber::amyNumber(float v)
{
	this->m_Value=v;
}
float& amyNumber::operator()()
{
	return this->m_Value;
}
	//
float amyNumber::operator=(float v)
{
	m_Value=v;
	return v;
}