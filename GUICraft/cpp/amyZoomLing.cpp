#include"amyZoomLing.h"
#include<QPainter>
#include"amyCube.h"
amyZoomLing::amyZoomLing(amyCanvas* can):amyImageLing(can)
{
	m_IsBeginToPan=0;

	this->SetInput(0);
	m_View=amyUtil::UNKNOWN;
	//m_ViewPort=can->rect();
}
void amyZoomLing::InitInput()
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	this->m_DesRect=GetDesRect();
	m_InputView=amyUtil::GetPlaneType(cube);
}
void amyZoomLing::wheelEvent ( QWheelEvent * event )
{
	int deg=event->delta()/20; //转15度 值是120 前转为正
	ZoomSrcRect(deg);
	emit s_srcregionzoomed(deg);
}
void amyZoomLing::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::MiddleButton)
	{
		if(this->GetCanvas()->cursor().shape()==Qt::ArrowCursor)
			this->GetCanvas()->setCursor(Qt::SizeAllCursor);
		m_IsBeginToPan=1;
		m_LastPoint = event->pos();
	}
}
void amyZoomLing::mouseMoveEvent(QMouseEvent * event)
{
	QPoint CurrentPoint;
	if((event->buttons()&Qt::MiddleButton)&&m_IsBeginToPan==1)
	{
		CurrentPoint   = event->pos();
		TranslateSrcRect(m_LastPoint-CurrentPoint);
		emit s_srcregiontranslated(m_LastPoint-CurrentPoint);
		m_LastPoint=CurrentPoint;
	}
}
void amyZoomLing::mouseReleaseEvent(QMouseEvent *)
{
	if(m_IsBeginToPan==1&&
		(this->GetCanvas()->cursor().shape()==Qt::SizeAllCursor)
		||(this->GetCanvas()->cursor().shape()==Qt::OpenHandCursor)
		||(this->GetCanvas()->cursor().shape()==Qt::PointingHandCursor))
		this->GetCanvas()->setCursor(Qt::ArrowCursor);
	m_IsBeginToPan=0;
}
void amyZoomLing::resizeEvent(QResizeEvent*)
{
	amyCube* c=this->GetInput();
	if(c==0)
		return;
	this->m_DesRect=GetDesRect();
	this->GetCanvas()->repaint();
}

QRect amyZoomLing::GetDesRect()
{
	QRect rect=this->GetCanvas()->rect();
	QRect srcrect=this->GetSrcRect();
	amyCube::tCube::SpacingType sp=this->GetInput()->obj->GetSpacing();
	if(this->GetInputView()==amyUtil::AXIAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			float v1=sp[0];
			float v2=sp[1];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			float v1=sp[0];
			float v2=sp[2];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			float v1=sp[1];
			float v2=sp[2];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
	}
	if(this->GetInputView()==amyUtil::CORONAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			float v1=sp[0];
			float v2=sp[2];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			float v1=sp[0];
			float v2=sp[1];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			float v1=sp[2];
			float v2=sp[1];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
	}
	if(this->GetInputView()==amyUtil::SAGITTAL)
	{
		if(this->GetView()==amyUtil::AXIAL)
		{
			float v1=sp[2];
			float v2=sp[0];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::CORONAL)
		{
			float v1=sp[2];
			float v2=sp[1];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
		if(this->GetView()==amyUtil::SAGITTAL)
		{
			float v1=sp[0];
			float v2=sp[1];
			srcrect.setWidth(float(srcrect.width())*v1/v2);
		}
	}
	//////////////////////////////////////////////
	int value=rect.height()*srcrect.width()-rect.width()*srcrect.height();
	int desw,desh;
	if(value>0)
	{
		desw=rect.width();
		desh=int(float(rect.width())/float(srcrect.width())*float(srcrect.height()));
	}
	else if(value<=0)
	{
		desw=float(rect.height())/float(srcrect.height())*float(srcrect.width());
		desh=rect.height();
	}
	//////////////////////////////////////////////
	
	int renderwidth=rect.width()<rect.height()?rect.width():rect.height();
	int hcenter=rect.width()/2;
	int vcenter=rect.height()/2;
	return QRect(hcenter-desw/2,vcenter-desh/2,desw,desh);
	//return QRect(hcenter-renderwidth/2,vcenter-renderwidth/2,renderwidth,renderwidth);
}

QPoint amyZoomLing::MapScreen2Cube(QPoint screen)
{
	int x=screen.x()-this->m_DesRect.left();
	int y=screen.y()-this->m_DesRect.top();
	float rax=(float)x/(float)this->m_DesRect.width();
	float ray=(float)y/(float)this->m_DesRect.height();
	int xx=rax*this->m_SrcRect.width()+m_SrcRect.left();
	int yy=ray*this->m_SrcRect.height()+m_SrcRect.top();
	return QPoint(xx,yy);
}
QPoint amyZoomLing::MapCube2Screen(QPoint cube)
{
	int x=cube.x()-this->m_SrcRect.left();
	int y=cube.y()-this->m_SrcRect.top();
	float rax=(float)x/(float)this->m_SrcRect.width();
	float ray=(float)y/(float)this->m_SrcRect.height();

	int xx=rax*this->m_DesRect.width()+m_DesRect.left();
	int yy=ray*this->m_DesRect.height()+m_DesRect.top();
	return QPoint(xx,yy);
}
void amyZoomLing::TranslateSrcRect(QPoint p)
{
	QRect r=m_DesRect.translated(-p);
	//if(m_MaxSrcRect.contains(r))
	{
		m_DesRect=r;
	}
	this->GetCanvas()->repaint();
}
void amyZoomLing::ZoomSrcRect(int deg)
{	
	float newbottom,newtop,newright,newleft;
	/////保持图像比例
	float m_ZoomFactorX=deg;
	float m_ZoomFactorY=(float)(deg*(float)m_DesRect.height()/(float)m_DesRect.width());
	newbottom=m_DesRect.bottom()+m_ZoomFactorY*4;
	newtop=m_DesRect.top()-m_ZoomFactorY*4;
	newright=m_DesRect.right()+m_ZoomFactorX*4;
	newleft =m_DesRect.left()-m_ZoomFactorX*4;
	if(newbottom>newtop&&newright>newleft)
	{
		m_DesRect.setBottom(newbottom);
		m_DesRect.setTop(newtop);
		m_DesRect.setLeft(newleft);
		m_DesRect.setRight(newright);
	}
	this->GetCanvas()->repaint();
	//int newbottom,newtop,newright,newleft;
	///////保持图像比例
	//int m_ZoomFactorX=deg;
	//int m_ZoomFactorY=(int)(deg*(float)m_MaxSrcRect.height()/(float)m_MaxSrcRect.width());
	//newbottom=m_SrcRect.bottom()-m_ZoomFactorY;
	//newtop=m_SrcRect.top()+m_ZoomFactorY;

	
	//if(newbottom<=newtop)	/////显示框过小
	//{
	//	newbottom=m_SrcRect.bottom();
	//	newtop=m_SrcRect.top();
	//}
	//else if(newtop<m_MaxSrcRect.top()&&newbottom<=m_MaxSrcRect.bottom())//上边界超过
	//{
	//	newbottom=m_SrcRect.bottom()-(2*m_ZoomFactorY-(m_MaxSrcRect.top()-m_SrcRect.top()));
	//	newtop=m_MaxSrcRect.top();
	//}
	//else if(newbottom>m_MaxSrcRect.bottom()&&newtop>=m_MaxSrcRect.top())//下边界超过
	//{
	//	newbottom=m_MaxSrcRect.bottom();
	//	newtop=m_SrcRect.top()+(2*m_ZoomFactorY-(m_SrcRect.bottom()-m_MaxSrcRect.bottom()));
	//}
	//else if(newbottom>=m_MaxSrcRect.bottom()&&newtop<=m_MaxSrcRect.top())//上下全超过
	//{
	//	newtop=m_MaxSrcRect.top();
	//	newbottom=m_MaxSrcRect.bottom();
	//}

	//newright=m_SrcRect.right()-m_ZoomFactorX;
	//newleft =m_SrcRect.left()+m_ZoomFactorX;
	//if(newright<=newleft)   ///显示框过小
	//{
	//	newright=m_SrcRect.right();
	//	newleft =m_SrcRect.left();
	//}
	//else if(newleft<m_MaxSrcRect.left()&&newright<=m_MaxSrcRect.right())//左边界超过
	//{
	//	newright=m_SrcRect.right()-(2*m_ZoomFactorX-(m_MaxSrcRect.left()-m_SrcRect.left()));
	//	newleft=m_MaxSrcRect.left();
	//}
	//else if(newright>m_MaxSrcRect.right()&&newleft>=m_MaxSrcRect.left())//右边界超过
	//{
	//	newright=m_MaxSrcRect.right();
	//	newleft=m_SrcRect.left()+(2*m_ZoomFactorX-(m_SrcRect.right()-m_MaxSrcRect.right()));
	//}
	//else if(newright>=m_MaxSrcRect.right()&&newleft<=m_MaxSrcRect.left())//左右都超过
	//{
	//	newright=m_MaxSrcRect.right();
	//	newleft=m_MaxSrcRect.left();
	//}
	//m_SrcRect.setBottom(newbottom);
	//m_SrcRect.setTop(newtop);
	//m_SrcRect.setLeft(newleft);
	//m_SrcRect.setRight(newright);
	//this->GetCanvas()->repaint();
}
void amyZoomLing::InitImage(QImage& image)
{
	m_SrcRect=QRect(0,0,image.width(),image.height());
	m_MaxSrcRect=m_SrcRect;
	this->m_DesRect=GetDesRect();
}
void amyZoomLing::RenderImage(QPaintDevice* dev,const QPixmap& pix)
{
	QPainter p(dev);
	p.drawPixmap(m_DesRect,pix,m_SrcRect);
}

void amyZoomLing::SetView(amyUtil::ePlane v)
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	//if(v==m_View)
	//	return;
	m_View=v;
	Init();
	Update();
}

bool amyZoomLing::IsOriginalView()
{
	return m_InputView==m_View?1:0;
}