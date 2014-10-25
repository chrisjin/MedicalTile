#include"amyCanvas.h"
#include"amyLing.h"
amyCanvas::amyCanvas(QWidget *parent)
	: QWidget(parent)
{
	//this->setFixedSize();
	this->setFocusPolicy(Qt::StrongFocus);
	QPalette p=this->palette();
	this->setAutoFillBackground(true);
	p = this->palette();
	//p.setColor(QPalette::Window,QColor(100,100,100));
	p.setColor(QPalette::Window,QColor(156,170,193));
	this->setPalette(p);
}

amyCanvas::~amyCanvas()
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		if(m_LingArr[i])
			delete m_LingArr[i];
	}
}
void amyCanvas::AddLing(amyLing* am)
{
	this->m_LingArr.push_back(am);
}
void amyCanvas::paintEvent(QPaintEvent *)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		if(m_LingArr[i]->IsShow())
			m_LingArr[i]->Render(this);
	}
}

void amyCanvas::mousePressEvent(QMouseEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mousePressEvent(event);
	}
}
void amyCanvas::mouseLeaveEvent(QMouseEvent *event)
{

}
void amyCanvas::mouseMoveEvent(QMouseEvent * event)
{
	if(!this->rect().contains(event->pos()))
	{
		for(int i=0;i<m_LingArr.size();i++)
		{
			m_LingArr[i]->mouseLeaveClientEvent(event);
		}
		mouseLeaveEvent(event);
	}
	else
	{
		for(int i=0;i<m_LingArr.size();i++)
		{
			m_LingArr[i]->mouseMoveEvent(event);
		}
	}
}
void amyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseReleaseEvent(event);
	}
}
void amyCanvas::mouseDoubleClickEvent(QMouseEvent * event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->mouseDoubleClickEvent(event);
	}
}
void amyCanvas::wheelEvent ( QWheelEvent * event )
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->wheelEvent(event);
	}
}
void amyCanvas::resizeEvent ( QResizeEvent * event )
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->resizeEvent(event);
	}
}

void amyCanvas::dropEvent(QDropEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->dropEvent(event);
	}
}
void amyCanvas::dragEnterEvent(QDragEnterEvent *event)
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->dragEnterEvent(event);
	}
}
void amyCanvas::keyPressEvent ( QKeyEvent * event )
{
	for(int i=0;i<m_LingArr.size();i++)
	{
		m_LingArr[i]->keyPressEvent(event);
	}
}
void amyCanvas::RemoveLing(amyLing* am)
{
	vector<amyLing*>::iterator itr=m_LingArr.begin();
	for(;itr!=m_LingArr.end();itr++)
	{
		if((*itr)==am)
			break;
	}
	m_LingArr.erase(itr);


}

void amyCanvas::ReplaceLing(amyLing* replaced,amyLing* newling)
{
	vector<amyLing*>::iterator itr=m_LingArr.begin();
	for(;itr!=m_LingArr.end();itr++)
	{
		if((*itr)==replaced)
			break;
	}
	delete *itr;
	newling->SetCanvas(this);
	*itr=newling;
}