#include"amyImageLing.h"
#include<QPainter>
amyImageLing::amyImageLing(amyCanvas* can):amyLing(can)
{
	m_IsInit=0;
}

void amyImageLing::InitImage(QImage& image)
{
}
void amyImageLing::UpdateImage(QImage& image)
{
}
QImage amyImageLing::DecorateImage(const QImage& Image)
{
	return Image;
}
void amyImageLing::Render(QPaintDevice* dev)
{
	if(m_IsInit==0)
		return;
	QPixmap pix=QPixmap::fromImage(DecorateImage(m_Image));
	RenderImage(dev,pix);
	RenderOthers(dev);
}
void amyImageLing::Init()
{
	InitImage(m_Image);
	m_IsInit=1;
}
void amyImageLing::Update()
{
	UpdateImage(m_Image);
}