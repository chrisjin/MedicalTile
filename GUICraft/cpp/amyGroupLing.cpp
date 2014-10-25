#include"amyGroupLing.h"

amyGroupLing::amyGroupLing(amyCanvas* can):amyLing(can)
{
}

void amyGroupLing::Render(QPaintDevice* dev)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		if(m_LingArr[i]->IsShow())
			m_LingArr[i]->Render(dev);
	}
}
void amyGroupLing::mousePressEvent(QMouseEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mousePressEvent(event);
	}
}
void amyGroupLing::mouseMoveEvent(QMouseEvent * event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseMoveEvent(event);
	}
}
void amyGroupLing::mouseReleaseEvent(QMouseEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseReleaseEvent(event);
	}
}
void amyGroupLing::mouseLeaveClientEvent(QMouseEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseLeaveClientEvent(event);
	}
}
void amyGroupLing::mouseDoubleClickEvent(QMouseEvent * event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseDoubleClickEvent(event);
	}
}
void amyGroupLing::wheelEvent ( QWheelEvent * event )
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->wheelEvent(event);
	}
}
void amyGroupLing::resizeEvent ( QResizeEvent * event )
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->resizeEvent(event);
	}
}
void amyGroupLing::AddLing(amyLing* am)
{
	this->m_LingArr.push_back(am);
}
void amyGroupLing::RemoveLing(amyLing* am)
{
	vector<amyLing*>::iterator itr=m_LingArr.begin();
	for(;itr!=m_LingArr.end();itr++)
	{
		if((*itr)==am)
			break;
	}
	m_LingArr.erase(itr);
}