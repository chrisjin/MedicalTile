//#include"amyChartLing.h"
//#include<QPaintDevice>
//#include"amyTypeWrap.h"
//#include<QPainter>
//amyChartLing::amyChartLing(amyCanvas* c):amyLing(c)
//{
//	this->SetInput(0);
//}
//void amyChartLing::InitInput()
//{
//	if(GetInput()==0)
//		return;
//	m_XMax=FLT_MIN;
//	m_XMin=FLT_MAX;
//	m_YMax=FLT_MIN;
//	m_YMin=FLT_MAX;
//	vector<amyPoint>& debug=this->GetInput()->pointarr;
//	for(int i=0;i<this->GetInput()->pointarr.size();i++)
//	{
//		if(this->GetInput()->pointarr[i].x<m_XMin)
//			m_XMin=this->GetInput()->pointarr[i].x;
//		if(this->GetInput()->pointarr[i].x>m_XMax)
//			m_XMax=this->GetInput()->pointarr[i].x;
//		if(this->GetInput()->pointarr[i].y<m_YMin)
//			m_YMin=this->GetInput()->pointarr[i].y;
//		if(this->GetInput()->pointarr[i].y>m_YMax)
//			m_YMax=this->GetInput()->pointarr[i].y;
//	}
//}
//void amyChartLing::Render(QPaintDevice* dev)
//{
//	amyPointArr* fa=this->GetInput();
//	if(fa==0)
//		return;
//	QPainter p(dev);
//	p.fillRect(this->GetCanvas()->rect(),QColor(100,100,100));
//
//	QRect frame=this->GetCanvas()->rect().adjusted(20,20,-20,-20);
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
//	QPoint *parr=new QPoint[fa->pointarr.size()];
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
//	for(int i=0;i<fa->pointarr.size();i++)
//	{
//		int x=frame.left()+(int)((fa->pointarr[i].x-m_XMin)*ratiox);
//		parr[i].setX(x);
//		int y=frame.bottom()-(int)((fa->pointarr[i].y-m_YMin)*ratioy);
//		parr[i].setY(y);
//		p.fillRect(QRect(QPoint(parr[i].x()-2,parr[i].y()-2),
//			QPoint(parr[i].x()+2,parr[i].y()+2)),QColor(200,0,0));
//	}
//	p.drawPolyline(parr,fa->pointarr.size());
//
//	//YAxis
//	for(int i=0;i<rectcount+1;i++)
//	{
//		float v=(float)i*exstep/ratioy+m_YMin;
//		p.setPen(Qt::green);
//		p.drawText(GetCanvas()->rect().left(),frame.bottom()-i*exstep,QString::number(v));
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
