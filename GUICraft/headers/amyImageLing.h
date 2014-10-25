#pragma once
#include"amyLing.h"
class GUI_INTERFACE amyImageLing:public amyLing
{
public:
	amyImageLing(amyCanvas* can);
	virtual void InitImage(QImage& image);
	virtual void UpdateImage(QImage& image);
	virtual QImage DecorateImage(const QImage& Image);
	virtual void Render(QPaintDevice* dev);
	virtual void RenderImage(QPaintDevice* dev,const QPixmap& pix)=0;
	virtual void RenderOthers(QPaintDevice* dev){}
	void Init();
	void Update();
private:
	QImage m_Image;
	bool   m_IsInit;
};