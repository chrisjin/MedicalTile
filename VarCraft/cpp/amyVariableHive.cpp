#include"amyVariableHive.h"
#include"amyVariableIO.h"
amyVariableHive::amyVariableHive()
{
	m_IO=0;
}
amyVariableIO*     amyVariableHive::CreateIO()
{
	return 0;
}
amyVariableIO*     amyVariableHive::GetIO()
{
	if(!m_IO)
	{
		m_IO=CreateIO();
		if(m_IO)
			m_IO->SetParent(this);
	}
	return m_IO;
}
