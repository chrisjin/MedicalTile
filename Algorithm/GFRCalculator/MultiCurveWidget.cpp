//#include"MultiCurveWidget.h"
//#include"amyTypeWrap.h"
//#include<QPainter>
//#define ISIN(index) (index>=m_PointBegin&&index<=m_PointEnd||(m_PointBegin==-1)||(m_PointEnd==-1))
//MultiCurveWidget::MultiCurveWidget(QWidget* parent):QWidget(parent)
//{
//	m_XMax=FLT_MIN;
//	m_XMin=FLT_MAX;
//	m_YMax=FLT_MIN;
//	m_YMin=FLT_MAX;
//	this->resize(800,600);
//	m_PointBegin=-1;
//	m_PointEnd=-1;
//}
//void MultiCurveWidget::AddPointArr(amyPointArr* pa)
//{
//	m_CurveArr.push_back(pa);
//	vector<amyPoint>& parr=pa->pointarr;
//	for(int i=0;i<parr.size();i++)
//	{
//		if(!ISIN(i))
//			continue;
//		if(parr[i].x<m_XMin)
//			m_XMin=parr[i].x;
//		if(parr[i].x>m_XMax)
//			m_XMax=parr[i].x;
//		if(parr[i].y<m_YMin)
//			m_YMin=parr[i].y;
//		if(parr[i].y>m_YMax)
//			m_YMax=parr[i].y;
//	}
//}
//void MultiCurveWidget::SetBound(int a,int b)
//{
//	m_PointBegin=a;
//	m_PointEnd=b;
//}
//void MultiCurveWidget::paintEvent(QPaintEvent *dev)
//{
//
//
//	QPainter p(this);
//	p.fillRect(this->rect(),QColor(100,100,100));
//
//	QRect frame=this->rect().adjusted(20,20,-20,-20);
//	p.drawRect(frame);
//
//	int rectcount=5;
//	int exstep=(frame.bottom()-frame.top())/rectcount;
//	for(int i=0;i<rectcount;i++)
//	{
//		QRect lr=frame;
//		lr.setTop(i*exstep+frame.top());
//		lr.setBottom((i+1)*exstep+frame.top());
//		int c=i%2?255:100;
//		p.fillRect(lr.adjusted(1,1,-1,-1),QColor(c,c,c));
//	}
//	
//
//	float ratioy;
//	if(m_YMax-m_YMin!=0)
//		ratioy=(float)(frame.bottom()-frame.top())/(m_YMax-m_YMin);
//	else
//		ratioy=1;
//
//	float ratiox;
//	if(m_XMax-m_XMin!=0)
//		ratiox=(float)(frame.right()-frame.left())/(m_XMax-m_XMin);
//	else
//		ratiox=1;
//	
//	for(int j=0;j<this->m_CurveArr.size();j++)
//	{
//		amyPointArr* fa=m_CurveArr[j];
//		int dif=m_PointEnd-m_PointBegin+1;
//		int pnum;
//		if(dif>1)
//		{
//			pnum=dif;
//		}
//		else
//		{
//			m_PointBegin=0;
//			m_PointEnd=fa->pointarr.size()-1;
//			pnum=fa->pointarr.size();
//		}
//		QPoint *parr=new QPoint[pnum];
//		QColor c=QColor(j%3*100,j%2*200,0);
//		for(int i=m_PointBegin;i<=m_PointEnd;i++)
//		{
//			if(i>=0&&i<fa->pointarr.size())
//			{
//				int x=frame.left()+(int)((fa->pointarr[i].x-m_XMin)*ratiox);
//				parr[i].setX(x);
//				int y=frame.bottom()-(int)((fa->pointarr[i].y-m_YMin)*ratioy);
//				parr[i].setY(y);
//				p.fillRect(QRect(QPoint(parr[i].x()-2,parr[i].y()-2),
//					QPoint(parr[i].x()+2,parr[i].y()+2)),c);
//			}
//		}
//		p.drawPolyline(parr,pnum);
//		delete[] parr;
//	}
//	//YAxis
//	for(int i=0;i<rectcount+1;i++)
//	{
//		float v=(float)i*exstep/ratioy+m_YMin;
//		p.setPen(Qt::green);
//		p.drawText(rect().left(),frame.bottom()-i*exstep,QString::number(v));
//		//p.restore();
//	}
//	int step=(m_XMax-m_XMin)/10;
//	for(int i=0;i<11;i++)
//	{
//		int x=frame.left()+(int)((i*step-m_XMin)*ratiox);
//		p.setPen(Qt::green);
//		p.drawText(x,frame.bottom()+20,QString::number(i*step));
//	}
//}