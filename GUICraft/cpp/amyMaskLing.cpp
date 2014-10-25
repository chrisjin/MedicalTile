#include"amyMaskLing.h"
#include<QPainter>
#include"amyCube.h"
#include"amyUtil.h"
amyMaskLing::amyMaskLing(amyCanvas* can):amyCubeLing(can)
{
	m_Mask=0;
	m_Transparency=100;
}
void amyMaskLing::InitInput()
{
	amyCube* cube=this->GetInput();
	if(cube==0)
		return;
	amyCube::tCube::SizeType size=cube->obj->GetLargestPossibleRegion().GetSize();
	m_MaskImage=QImage(size[0],size[1],QImage::Format_ARGB32);
	amyUtil::GetCubeMinMax(cube,m_Min,m_Max);

	amyCubeLing::InitInput();
}
void amyMaskLing::SetTransparency(int a)
{
	m_Transparency=a;
	Update();
}
void amyMaskLing::UpdateImage(QImage& image)
{
	
	UpdateMaskImage();
	amyCubeLing::UpdateImage(image);
}
QImage  amyMaskLing::DecorateImage(const QImage& image)
{
	QImage img=QImage(image.width(),image.height(),QImage::Format_ARGB32);
	QPainter p(&img);
	//p.setPen(Qt::yellow);
	p.drawImage(QPoint(0,0),image);
	p.drawImage(QPoint(0,0),m_MaskImage);
	
	return img;
}
void amyMaskLing::UpdateMaskImage()
{
	if(this->m_Mask==0)
		return;
	for(int i=0;i<m_MaskImage.width();i++)
		for(int j=0;j<m_MaskImage.height();j++)
		{
			amyCube::tCube::IndexType index;
			index[0]=i;
			index[1]=j;
			index[2]=this->GetSlice();
			if(m_Mask->obj->GetPixel(index)>0)
				m_MaskImage.setPixel(i,j,qRgba(255,0,0,m_Transparency));
			else
				m_MaskImage.setPixel(i,j,qRgba(0,0,0,0));
		}
}
void amyMaskLing::SetMask(amyCube* c)
{
	this->m_Mask=c;
	this->GetCanvas()->repaint();
}