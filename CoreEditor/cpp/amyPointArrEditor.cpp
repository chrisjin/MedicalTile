//#include"amyPointArrEditor.h"
//#include"amyTypeWrap.h"
//#include<QPainter>
//#include<QTableWidget>
//#include<QVBoxLayout>
//#include<QEvent>
//#include<QKeyEvent>
//#include<QApplication>
//#include<QClipboard>
//#include"amyChartLing.h"
//amyChartXYWidget::amyChartXYWidget(QWidget* parent):amyCanvas(parent)
//{
//	this->SetInput(0);
//}
//void amyChartXYWidget::InitInput()
//{
//	if(GetInput()==0)
//		return;
//	m_ChartLing=new amyChartLing(this);
//	m_ChartLing->SetInput(GetInput());
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
////void amyChartXYWidget::paintEvent(QPaintEvent *dev)
////{
////	amyPointArr* fa=this->GetInput();
////	if(fa==0)
////		return;
////	QPainter p(this);
////	p.fillRect(this->rect(),QColor(100,100,100));
////
////	QRect frame=this->rect().adjusted(20,20,-20,-20);
////	p.drawRect(frame);
////
////	int rectcount=5;
////	int exstep=(frame.bottom()-frame.top())/rectcount;
////	for(int i=0;i<rectcount;i++)
////	{
////		QRect lr=frame;
////		lr.setTop(i*exstep+frame.top());
////		lr.setBottom((i+1)*exstep+frame.top());
////		int c=i%2?255:100;
////		p.fillRect(lr.adjusted(1,1,-1,-1),QColor(c,c,c));
////	}
////	
////	QPoint *parr=new QPoint[fa->pointarr.size()];
////
////	float ratioy;
////	if(m_YMax-m_YMin!=0)
////		ratioy=(float)(frame.bottom()-frame.top())/(m_YMax-m_YMin);
////	else
////		ratioy=1;
////
////	float ratiox;
////	if(m_XMax-m_XMin!=0)
////		ratiox=(float)(frame.right()-frame.left())/(m_XMax-m_XMin);
////	else
////		ratiox=1;
////
////	for(int i=0;i<fa->pointarr.size();i++)
////	{
////		int x=frame.left()+(int)((fa->pointarr[i].x-m_XMin)*ratiox);
////		parr[i].setX(x);
////		int y=frame.bottom()-(int)((fa->pointarr[i].y-m_YMin)*ratioy);
////		parr[i].setY(y);
////		p.fillRect(QRect(QPoint(parr[i].x()-2,parr[i].y()-2),
////			QPoint(parr[i].x()+2,parr[i].y()+2)),QColor(200,0,0));
////	}
////	p.drawPolyline(parr,fa->pointarr.size());
////
////	//YAxis
////	for(int i=0;i<rectcount+1;i++)
////	{
////		float v=(float)i*exstep/ratioy+m_YMin;
////		p.setPen(Qt::green);
////		p.drawText(rect().left(),frame.bottom()-i*exstep,QString::number(v));
////		//p.restore();
////	}
////	int step=(m_XMax-m_XMin)/10;
////	for(int i=0;i<11;i++)
////	{
////		int x=frame.left()+(int)((i*step-m_XMin)*ratiox);
////		p.setPen(Qt::green);
////		p.drawText(x,frame.bottom()+20,QString::number(i*step));
////	}
////}
//
//
//amyPointArrEditor::amyPointArrEditor(QWidget *parent)
//{
//	QVBoxLayout* l=new QVBoxLayout(this);
//	QWidget* w=this->GetMainWidget();
//	w->setLayout(l);
//	QHBoxLayout* hl=new QHBoxLayout(this);
//	//QPushButton *copy1=new QPushButton("¸´ÖÆµ½")
//	
//	m_Table=new QTableWidget(this);
//	m_Table->installEventFilter(this);
//	l->addWidget(m_Table,1);
//	m_Chart=new amyChartXYWidget(this);
//	l->addWidget(m_Chart,4);
//
//	resize(800,600);
//}
//void amyPointArrEditor::InitInput()
//{
//	amyPointArr::Keeper arr=this->GetInput().Get<amyPointArr>();
//	m_Table->setRowCount(2);
//	m_Table->setColumnCount(arr->pointarr.size());
//	for(int i=0;i<arr->pointarr.size();i++)
//	{
//		QTableWidgetItem* item=new QTableWidgetItem(QString::number(arr->pointarr[i].x));
//		m_Table->setItem(0,i,item);
//		item=new QTableWidgetItem(QString::number(arr->pointarr[i].y));
//		m_Table->setItem(1,i,item);
//	}
//
//	m_Chart->SetInput(arr.GetPointer());
//	m_Chart->repaint();
//	amyVariableEditor::InitInput();
//}
//void amyPointArrEditor::Confirm()
//{
//	amyPointArr::Keeper arr=this->GetInput().Get<amyPointArr>();
//	for(int i=0;i<m_Table->columnCount();i++)
//	{
//		QByteArray ba = m_Table->item(0,i)->text().toLatin1();
//		arr->pointarr[i].x=atof(ba.data());
//		ba = m_Table->item(1,i)->text().toLatin1();
//		arr->pointarr[i].y=atof(ba.data());
//	}
//	amyVariableEditor::Confirm();
//}
//
//bool amyPointArrEditor::eventFilter(QObject *target, QEvent *event)
//{
//	if(target==this->m_Table)
//	{
//		if(event->type()==QEvent::KeyPress)
//		{
//			keyTablePressEvent(static_cast<QKeyEvent*>(event));
//			return 1;
//		}
//	}
//	return amyVariableEditor::eventFilter(target,event);
//}
//
//void amyPointArrEditor::keyTablePressEvent(QKeyEvent*event)
//{
//	if(event->matches(QKeySequence::Copy))
//	{
//		Copy();
//	}
//}
//
//void amyPointArrEditor::Copy()
//{
//	amyVariable v=this->GetInput();
//	int  cc=m_Table->columnCount();;
//	amyPointArr::Keeper k=v.Get<amyPointArr>();
//	QString str="";
//	for(int i=0;i<cc;i++)
//	{
//		QModelIndex index=m_Table->model()->index(0,i);
//		if(m_Table->selectionModel()->isSelected(index))
//		{
//			str+=QString::number(k->pointarr[index.column()].x);
//			str+="\t";
//		}
//		index=m_Table->model()->index(1,i);
//		if(m_Table->selectionModel()->isSelected(index))
//		{
//			str+=QString::number(k->pointarr[index.column()].y);
//			str+="\t";
//		}
//	}
//	QApplication::clipboard()->setText(str);
//}