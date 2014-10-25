#include"amyAnnotationLing.h"
#include"amyDICOM.h"
#include<QPainter>
#include<QFont>
#include"amyCube.h"
#include"itkImage.h"
#include"amyUtil.h"
#include"amyCubeLing.h"
amyAnnotationLing::amyAnnotationLing(amyCubeLing* cubeling,amyCanvas* can):amyLing(can)
{
	m_CurrentSlice=0;
	this->SetCubeLing(cubeling);

}

void amyAnnotationLing::UpdateStr()
{
	TopLeft=QString("No.: ")+ImageNum+"/"+ImageCount+"\n"
		+QString("IM: ")+ImageNumInDICOM+"\n"
		+PlaneType;
	BottomLeft=m_PixelValue+"\n";
	BottomLeft=VoxelSize+"\n"+BottomLeft+WindowInfo+"\n"
		+QString("T: ")+SliceThickness+"  "+QString("L: ")+SliceLocation;
	TopRight=PatientName;

	switch(this->m_CubeLing->GetView())
	{
	case amyUtil::AXIAL:
		Top="A";
		Bottom="P";
		Left="R";
		Right="L";
		break;
	case amyUtil::CORONAL:
		Left="R";
		Right="L";
		Top="S";
		Bottom="I";
		break;
	case amyUtil::SAGITTAL:
		Top="S";
		Bottom="I";
		Left="A";
		Right="P";
		break;
	}
}

QString GetWindowStr(int windowcenter,int windowwidth)
{
	QString center=QString::number(windowcenter);
	QString width=QString::number(windowwidth);
	return QString("WL: ")+center+QString("  ")+QString("WW: ")+width;
}
void amyAnnotationLing::SetPixelValue(int x,int y,int v,bool isshow)
{
	if(isshow)
	{
		m_PixelValue=QString("X: ")+QString::number(x)+" "+QString("Y: ")+QString::number(y)+" "
			+QString("Val: ")+QString::number(v);
	}
	else
	{
		m_PixelValue="";
	}
}
void amyAnnotationLing::SetCubeLingInput()
{
	this->SetCubeLing(m_CubeLing);
}
void amyAnnotationLing::SetCubeLing(amyCubeLing* cubeling)
{
	this->m_CubeLing=cubeling;
	connect(cubeling,SIGNAL(s_inputchanged()),this,SLOT(SetCubeLingInput()));
	connect(cubeling,SIGNAL(s_slicechanging(int)),this,SLOT(SetSlice(int)));
	amyCube  * cub=this->m_CubeLing->GetInput();
	if(cub==0)
		return;
	//Calculate(cub);
	amyUtil::ePlane p=amyUtil::GetPlaneType(cub);
	switch(p)
	{
	case amyUtil::AXIAL:
		PlaneType="Plane: AXIAL";
		break;
	case amyUtil::CORONAL:
		PlaneType="Plane: CORONAL";
		break;
	case amyUtil::SAGITTAL:
		PlaneType="Plane: SAGITTAL";
		break;
	default:
		PlaneType="Plane: UNKNOWN";
		break;
	}
	amyKeeper<amySeries> ser=cub->series;
	amyCube::tCube::SpacingType sp=cub->obj->GetSpacing();
	VoxelSize=QString::number(sp[0])+" X "+QString::number(sp[1])+" X "+QString::number(sp[2]);
	//amySeriesInfo::ePlane tp=cub->series->info->plane;
	ImageNum=QString::number(m_CurrentSlice+1);
	if(!ser.IsNull())
	{
		ImageCount = QString::number(ser->slicearr.size());
		SetWindow(ser->slicearr[0]->info->windowcenter,ser->slicearr[0]->info->windowwidth);
	}
	else
	{
		if(cub->obj.IsNull())
			return;
		amyCube::tCube::RegionType region = cub->obj->GetLargestPossibleRegion();
		amyCube::tCube::SizeType size     = region.GetSize();
		ImageCount                        = QString::number(size[2]);
		SetWindow(cub->windowcenter,cub->windowwidth);
	}
}
//void amyAnnotationLing::InitInput()
//{
//	amyCubeLing  * cub=this->GetInput();
//	if(cub==0)
//		return;
//	//Calculate(cub);
//	amyUtil::ePlane p=amyUtil::GetPlaneType(cub->GetInput());
//	switch(p)
//	{
//	case amyUtil::AXIAL:
//		PlaneType="Plane: AXIAL";
//		break;
//	case amyUtil::CORONAL:
//		PlaneType="Plane: CORONAL";
//		break;
//	case amyUtil::SAGITTAL:
//		PlaneType="Plane: SAGITTAL";
//		break;
//	default:
//		PlaneType="Plane: UNKNOWN";
//		break;
//	}
//	amyKeeper<amySeries> ser=cub->series;
//	//amySeriesInfo::ePlane tp=cub->series->info->plane;
//	ImageNum=QString::number(m_CurrentSlice+1);
//	if(!ser.IsNull())
//	{
//		ImageCount = QString::number(ser->slicearr.size());
//		SetWindow(ser->slicearr[0]->info->windowcenter,ser->slicearr[0]->info->windowwidth);
//	}
//	else
//	{
//		if(cub->obj.IsNull())
//			return;
//		amyCube::tCube::RegionType region = cub->obj->GetLargestPossibleRegion();
//		amyCube::tCube::SizeType size     = region.GetSize();
//		ImageCount                        = QString::number(size[2]);
//		SetWindow(cub->windowcenter,cub->windowwidth);
//	}
//}
void amyAnnotationLing::SetSlice(int index)
{
	amyCube *cub=m_CubeLing->GetInput();
	if(cub==0)
		return;
	if(index==m_CurrentSlice)
		return;
	amyKeeper<amySeries> ser=cub->series;
	m_CurrentSlice=index;
	if(!ser.IsNull())
	{
		ImageNum=QString::number(index+1);
		if(this->m_CubeLing->IsOriginalView())
		{
			ImageNumInDICOM = QString::number(ser->slicearr[index]->info->imagenumber);
			SliceLocation   = QString::number(ser->slicearr[index]->info->slicelocation);
			SliceThickness  = QString::number(ser->slicearr[index]->info->slicethickness);
		}
		if(!ser->patientinfo.IsNull())
		{
			PatientName=ser->patientinfo->name.c_str();
		}
	}
	else
	{
		if(cub->obj.IsNull())
			return;
		ImageNum=QString::number(index+1);
		amyCube::tCube::SpacingType spacing=cub->obj->GetSpacing();
		amyCube::tCube::PointType ori=cub->obj->GetOrigin();
		SliceLocation=QString::number(ori[2]+spacing[2]*index);
		SliceThickness=QString::number(spacing[2]);
		PatientName="UNKNOWN";
		ImageNumInDICOM="NONE";
	}
	this->GetCanvas()->repaint();
}
void amyAnnotationLing::resizeEvent(QResizeEvent*)
{
	QRect rect=this->GetCanvas()->rect();
	this->SetRect(amyRect(rect.x(),rect.y(),rect.width(),rect.height()));
}
void amyAnnotationLing::SetWindow(int c,int w)
{
	WindowInfo=GetWindowStr(c,w);
}
void amyAnnotationLing::Render(QPaintDevice* dev)
{
	if(m_CubeLing->GetInput()==0)
		return;
	if(m_CubeLing->GetInput()->obj.IsNull())
		return;
	QPainter p(dev);
	QRect rect=this->GetCanvas()->rect();
	p.setPen(Qt::yellow);
	QFont font;
	font.setStyleHint(QFont::Fantasy);
	font.setPixelSize(16);
	p.setFont(font);
	UpdateStr();
	p.drawText(rect,Qt::AlignTop|Qt::AlignLeft,TopLeft);
	p.drawText(rect,Qt::AlignTop|Qt::AlignRight,TopRight);
	p.drawText(rect,Qt::AlignBottom|Qt::AlignLeft,BottomLeft);
	switch(this->m_CubeLing->GetView())
	{
	case amyUtil::AXIAL:
		p.setPen(Qt::red);
		break;
	case amyUtil::CORONAL:
		p.setPen(Qt::green);
		break;
	case amyUtil::SAGITTAL:
		p.setPen(Qt::blue);
		break;
	}
	p.drawText(rect,Qt::AlignTop|Qt::AlignHCenter,Top);
	p.drawText(rect,Qt::AlignBottom|Qt::AlignHCenter,Bottom);
	p.drawText(rect,Qt::AlignLeft|Qt::AlignVCenter,Left);
	p.drawText(rect,Qt::AlignRight|Qt::AlignVCenter,Right);
	//p.drawt
	//p.drawText(QPoint(rect.width(),0),"LK");
}