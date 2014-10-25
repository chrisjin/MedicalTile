//#include"amyFloatArrEditor.h"
//#include<QHBOXLayout>
//#include<QTableWidget>
//#include"amyTypeWrap.h"
//#include<QPainter>
//#include<QPaintDevice>
//#include<QMatrix >
//#include<QPushButton>
//#include<QEvent>
//#include<QKeyEvent>
//#include<QApplication>
//#include<QClipBoard>
//#include<QTableWidgetSelectionRange>
//amyChartWidget::amyChartWidget(QWidget* parent):QWidget(parent)
//{
//	this->SetInput(0);
//}
//void amyChartWidget::InitInput()
//{
//	if(GetInput()==0)
//		return;
//	m_Max=FLT_MIN;
//	m_Min=FLT_MAX;
//	for(int i=0;i<this->GetInput()->arr.size();i++)
//	{
//		if(this->GetInput()->arr[i]<m_Min)
//			m_Min=this->GetInput()->arr[i];
//		if(this->GetInput()->arr[i]>m_Max)
//			m_Max=this->GetInput()->arr[i];
//	}
//}
//void amyChartWidget::paintEvent(QPaintEvent *dev)
//{
//	amyFloatArr* fa=this->GetInput();
//	if(fa==0)
//		return;
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
//	int xstep;
//	if(fa->arr.size()-1)
//		xstep=(frame.right()-frame.left())/(fa->arr.size()-1);
//	else
//		xstep=0;
//	QPoint *parr=new QPoint[fa->arr.size()];
//	float ratio;
//	if(m_Max-m_Min!=0)
//		ratio=(float)(frame.bottom()-frame.top())/(m_Max-m_Min);
//	else
//		ratio=1;
//	for(int i=0;i<fa->arr.size();i++)
//	{
//		parr[i].setX(frame.left()+xstep*i);
//		int y=frame.bottom()-(int)((fa->arr[i]-m_Min)*ratio);
//		parr[i].setY(y);
//		p.fillRect(QRect(QPoint(parr[i].x()-2,parr[i].y()-2),
//			QPoint(parr[i].x()+2,parr[i].y()+2)),QColor(200,0,0));
//	}
//	p.drawPolyline(parr,fa->arr.size());
//
//	//YAxis
//	for(int i=0;i<rectcount+1;i++)
//	{
//		float v=(float)i*exstep/ratio+m_Min;
//		//QMatrix mat;
//		//p.save();
//		//p.translate(rect().left(),frame.bottom()+i*exstep);
//		//p.rotate(-45);
//		p.setPen(Qt::green);
//		p.drawText(rect().left(),frame.bottom()-i*exstep,QString::number(v));
//		//p.restore();
//	}
//}
//
//amyFloatArrEditor::amyFloatArrEditor(QWidget *parent)
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
//	m_Chart=new amyChartWidget(this);
//	l->addWidget(m_Chart,4);
//
//	resize(800,500);
//}
//void amyFloatArrEditor::InitInput()
//{
//	amyFloatArr::Keeper arr=this->GetInput().Get<amyFloatArr>();
//	m_Table->setRowCount(1);
//	m_Table->setColumnCount(arr->arr.size());
//	for(int i=0;i<arr->arr.size();i++)
//	{
//		QTableWidgetItem* item=new QTableWidgetItem(QString::number(arr->arr[i]));
//		m_Table->setItem(0,i,item);
//	}
//
//	m_Chart->SetInput(arr.GetPointer());
//	m_Chart->repaint();
//	amyVariableEditor::InitInput();
//}
//void amyFloatArrEditor::Confirm()
//{
//	amyFloatArr::Keeper arr=this->GetInput().Get<amyFloatArr>();
//	for(int i=0;i<m_Table->columnCount();i++)
//	{
//		QByteArray ba = m_Table->item(0,i)->text().toLatin1();
//		arr->arr[i]=atof(ba.data());
//	}
//	amyVariableEditor::Confirm();
//}
//
//bool amyFloatArrEditor::eventFilter(QObject *target, QEvent *event)
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
//void amyFloatArrEditor::keyTablePressEvent(QKeyEvent*event)
//{
//	if(event->matches(QKeySequence::Copy))
//	{
//		Copy();
//	}
//}
//
//void amyFloatArrEditor::Copy()
//{
//	amyVariable v=this->GetInput();
//	int  cc=m_Table->columnCount();;
//	amyFloatArr::Keeper k=v.Get<amyFloatArr>();
//	QString str="";
//	for(int i=0;i<cc;i++)
//	{
//		QModelIndex index=m_Table->model()->index(0,i);
//		if(m_Table->selectionModel()->isSelected(index))
//		{
//			str+=QString::number(k->arr[index.column()]);
//			str+="\t";
//		}
//	}
//	QApplication::clipboard()->setText(str);
//}