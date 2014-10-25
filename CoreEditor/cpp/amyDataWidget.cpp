#include"amyDataWidget.h"
#include<set>
#include<QMap>
#include<QPainter>
using namespace std;
void DataModel::Notify()
{
	emit s_changed();
}
amyDataWidget::amyDataWidget(QWidget* parent):QWidget(parent)
{
	m_XShowLine=0;
	m_YShowLine=0;
}

void amyDataWidget::SetModel(amyKeeper<DataModel> model)
{
	m_DataModel=model;
	////////统计多少个X 多少Y
	Update();
	connect(m_DataModel.GetPointer(),SIGNAL(s_changed()),this,SLOT(Update()));
}

void amyDataWidget::Update()
{
	m_CurveArr.clear();
	//////////初始化这些数
	m_XMax=-FLT_MAX;
	m_XMin=FLT_MAX;
	m_YMax=-FLT_MAX;
	m_YMin=FLT_MAX;
	//////////按Pair分组
	QMap<int,vector<int>> Pair2Index;
	for(int i=0;i<m_DataModel->axisrole.size();i++)
	{
		Pair2Index[m_DataModel->pairrole[i]].push_back(i);
	}

	QMap<int,vector<int>>::iterator itr=Pair2Index.begin();
	for(;itr!=Pair2Index.end();itr++)
	{
		vector<int>& indexarr=itr.value();
		amyKeeper<amyArray> xarr;
		for(int i=0;i<indexarr.size();i++)
		{
			if(m_DataModel->axisrole[indexarr[i]]==DataModel::X)
			{
				xarr=m_DataModel->totaldata[indexarr[i]];
				break;
			}
		}
		for(int i=0;i<indexarr.size();i++)
		{
			if(m_DataModel->axisrole[indexarr[i]]==DataModel::Y)
			{
				amyKeeper<tCurve> c=new tCurve;
				amyKeeper<amyArray> yarr=m_DataModel->totaldata[indexarr[i]];
				QColor colorrole=m_DataModel->colorrole[indexarr[i]];
				int num=0;
				if(!xarr.IsNull()&&!yarr.IsNull())
				{
					int xsize=xarr->size();
					int ysize=yarr->size();
					num=xsize<ysize?xsize:ysize;
				}
				else if(xarr.IsNull())
					num=-1;
				if(num==-1)
				{
					for(int i=0;i<yarr->size();i++)
					{
						float y=yarr->at(i);
						float x=i;
						c->pointarr.push_back(amyPoint(x,y));
						c->color=colorrole;
						if(x>m_XMax)m_XMax=x;
						if(x<m_XMin)m_XMin=x;
						if(y>m_YMax)m_YMax=y;
						if(y<m_YMin)m_YMin=y;
					}
				}
				else
				{
					for(int i=0;i<num;i++)
					{
						float y=yarr->at(i);
						float x=xarr->at(i);
						c->pointarr.push_back(amyPoint(x,y));
						c->color=colorrole;
						if(x>m_XMax)m_XMax=x;
						if(x<m_XMin)m_XMin=x;
						if(y>m_YMax)m_YMax=y;
						if(y<m_YMin)m_YMin=y;
					}
				
				}
				m_CurveArr.push_back(c);
			}
		}
	}
	UpdateChartBound();

	m_XTrLow=m_XMin;
	m_XTrHigh=m_XMax;
	m_YTrLow=m_YMin;
	m_YTrHigh=m_YMax;
	emit s_xyrangechanged();
	repaint();
}
void amyDataWidget::GetXYRange(float& xmin,float& xmax,float& ymin,float& ymax)
{
	xmin=m_XMin;
	xmax=m_XMax;
	ymin=m_YMin;
	ymax=m_YMax;
}
void amyDataWidget::Crop()
{
	m_XMax=-FLT_MAX;
	m_XMin=FLT_MAX;
	m_YMax=-FLT_MAX;
	m_YMin=FLT_MAX;
	for(int i=0;i<m_CurveArr.size();i++)
	{
		amyKeeper<tCurve> c=m_CurveArr[i];
		if(c.IsNull())
			continue;
		for(int j=0;j<c->pointarr.size();j++)
		{
			float x=c->pointarr.at(j).x;
			float y=c->pointarr.at(j).y;
			if(x>=m_XTrLow&&x<=m_XTrHigh&&y>=m_YTrLow&&y<=m_YTrHigh)
			{
				if(x>m_XMax)m_XMax=x;
				if(x<m_XMin)m_XMin=x;
				if(y>m_YMax)m_YMax=y;
				if(y<m_YMin)m_YMin=y;
			}
		}
	}
	UpdateChartBound();
}
void amyDataWidget::XThresholdChanging(float a,float b)
{
	m_XTrLow=a;
	m_XTrHigh=b;
	m_XShowLine=1;
	this->repaint();
}
void amyDataWidget::XThresholdChanged(float a,float b)
{
	m_XTrLow=a;
	m_XTrHigh=b;
	Crop();
	m_XShowLine=0;
	this->repaint();
}
void amyDataWidget::YThresholdChanging(float a,float b)
{
	m_YTrLow=a;
	m_YTrHigh=b;
	m_YShowLine=1;
	this->repaint();
}
void amyDataWidget::YThresholdChanged(float a,float b)
{
	m_YTrLow=a;
	m_YTrHigh=b;
	Crop();
	m_YShowLine=0;
	this->repaint();
}
int    amyDataWidget::MapToWidgetX(float num)
{
	return m_Frame.left()+(int)((num-m_XMin)*m_XRatio);
}
int    amyDataWidget::MapToWidgetY(float num)
{
	return m_Frame.bottom()-(int)((num-m_YMin)*m_YRatio);
}
float  amyDataWidget::MapFromWidgetX(int num)
{
	return float(num-m_Frame.left())/m_XRatio+m_XMin;
}
float  amyDataWidget::MapFromWidgetY(int num)
{
	return float(m_Frame.bottom()-num)/m_YRatio+m_YMin;
}
void amyDataWidget::UpdateChartBound()
{
	m_Frame=this->rect().adjusted(40,20,-20,-20);
	if(m_YMax-m_YMin!=0)
		m_YRatio=(float)(m_Frame.bottom()-m_Frame.top())/(m_YMax-m_YMin);
	else
		m_YRatio=1;

	float ratiox;
	if(m_XMax-m_XMin!=0)
		m_XRatio=(float)(m_Frame.right()-m_Frame.left())/(m_XMax-m_XMin);
	else
		m_XRatio=1;
}
void amyDataWidget::resizeEvent ( QResizeEvent * event )
{
	UpdateChartBound();
}
void amyDataWidget::paintEvent(QPaintEvent *dev)
{
	QPainter p(this);
	p.fillRect(this->rect(),QColor(100,100,100));
	p.drawRect(m_Frame);

	int rectcount=5;
	int exstep=(m_Frame.bottom()-m_Frame.top())/rectcount;
	for(int i=0;i<rectcount;i++)
	{
		QRect lr=m_Frame;
		lr.setTop(i*exstep+m_Frame.top());
		lr.setBottom((i+1)*exstep+m_Frame.top());
		int c=i%2?255:100;
		p.fillRect(lr.adjusted(1,1,-1,-1),QColor(c,c,c));
	}
		//YAxis
	for(int i=0;i<rectcount+1;i++)
	{
		float v=(float)i*exstep/m_YRatio+m_YMin;
		QRect tr=QRect(rect().left(),m_Frame.bottom()-i*exstep-20,38,20);
		QString str=QString::number(v);
		if(str.size()>=6)
			str.truncate(6);
		p.setPen(Qt::black);
		p.drawText(tr,Qt::AlignRight|Qt::AlignBottom,str);
		//p.restore();
	}
	//XAxis
	float step=(m_XMax-m_XMin)/10;
	for(int i=0;i<11;i++)
	{
		//int x=m_Frame.left()+(int)((i*step-m_XMin)*m_XRatio);
		int x=this->MapToWidgetX(i*step+m_XMin);
		QRect tr=QRect(x,m_Frame.bottom(),40,20);
		p.setPen(Qt::black);
		p.drawText(tr,Qt::AlignVCenter|Qt::AlignLeft,QString::number(i*step+m_XMin));

		p.drawLine(x,m_Frame.bottom(),x,m_Frame.bottom()-2);
		//p.drawText(x,m_Frame.bottom()+20,QString::number(i*step+m_XMin));
	}

	p.setRenderHint(QPainter::Antialiasing);
	for(int j=0;j<this->m_CurveArr.size();j++)
	{
		amyKeeper<tCurve> fa=m_CurveArr[j];
		int pnum=fa->pointarr.size();
		QPolygon polyline;
		QColor c=fa->color;
		for(int i=0;i<=pnum;i++)
		{
			if(i>=0&&i<fa->pointarr.size())
			{
				float xv=fa->pointarr.at(i).x;
				float yv=fa->pointarr.at(i).y;
				int x=MapToWidgetX(xv);
				int y=MapToWidgetY(fa->pointarr.at(i).y);
				QPoint ptodraw=QPoint(x,y);
				if(xv<=m_XTrHigh&&xv>=m_XTrLow&&yv<=m_YTrHigh&&yv>=m_YTrLow)
				{
					polyline.append(ptodraw);
					p.fillRect(QRect(QPoint(ptodraw.x()-2,ptodraw.y()-2),
						QPoint(ptodraw.x()+2,ptodraw.y()+2)),c);
				}
			}
		}
		p.drawPolyline(polyline);
	}

	QPen pen;
	pen.setBrush(Qt::yellow);
	pen.setStyle(Qt::PenStyle::DashLine);
	p.setPen(pen);
	
	int x1=this->MapToWidgetX(this->m_XTrLow);
	int x2=this->MapToWidgetX(this->m_XTrHigh);
	if(m_XShowLine)
	{
		p.drawLine(x1,m_Frame.bottom(),x1,m_Frame.top());
		p.drawLine(x2,m_Frame.bottom(),x2,m_Frame.top());
	}

	int y1=this->MapToWidgetY(this->m_YTrLow);
	int y2=this->MapToWidgetY(this->m_YTrHigh);
	if(m_YShowLine)
	{
		p.drawLine(m_Frame.left(),y1,m_Frame.right(),y1);
		p.drawLine(m_Frame.left(),y2,m_Frame.right(),y2);
	}
}

void amyDataWidget::mousePressEvent(QMouseEvent *event)
{

}

void amyDataWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void amyDataWidget::mouseReleaseEvent(QMouseEvent *event)
{

}