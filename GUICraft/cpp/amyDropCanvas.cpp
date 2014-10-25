#include"amyDropCanvas.h"
#include"amyShuttle.h"
#include<QDragEnterEvent>
amyDropCanvas::amyDropCanvas(QWidget* p):amyCanvas(p)
{
}
void amyDropCanvas::dropEvent(QDropEvent *event)
{
	VTYPE type=amyShuttle::GetInstance()->GetType();
	this->setFocus();
	switch(type)
	{
		case VTYPE_SERIES:
			{
				amyKeeper<amySeries> ser=amyShuttle::GetInstance()->GetData().CastTo<amySeries>();
				if(OnAcceptSeries(ser))
				{
					emit s_dropped();
					repaint();
				}
			}
			break;
		case VTYPE_CUBE:
			{
				amyKeeper<amyCube> cube=amyShuttle::GetInstance()->GetData().CastTo<amyCube>();
				if(OnAcceptCube(cube))
				{
					emit s_dropped();
					repaint();
				}
			}
			break;
	}
}
void amyDropCanvas::dragEnterEvent(QDragEnterEvent *event)
{
	VTYPE type=amyShuttle::GetInstance()->GetType();
	if(IsAccept(type))
	{
		 event->acceptProposedAction();
	}
}
bool amyDropCanvas::IsAccept(VTYPE t)
{
	return 0;
}
bool amyDropCanvas::OnAcceptSeries(amyKeeper<amySeries> k)
{
	return 0;
}
bool amyDropCanvas::OnAcceptCube(amyKeeper<amyCube> k)
{
	return 0;
}