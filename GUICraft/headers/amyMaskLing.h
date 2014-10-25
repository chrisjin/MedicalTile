#pragma once
#include"amyCubeLing.h"
class GUI_INTERFACE amyMaskLing:public amyCubeLing
{
public:
	amyMaskLing(amyCanvas* can);
	virtual void UpdateImage(QImage& image);
	virtual QImage DecorateImage(const QImage& image);
	virtual void InitInput();
	void SetMask(amyCube* c);
	amyCube* GetMask(){return m_Mask;}
	void SetTransparency(int a);
	int GetMax(){return m_Max;}
	int GetMin(){return m_Min;}
	void UpdateMaskImage();
private:
	int m_Min;
	int m_Max;
	int m_Transparency;
	amyCube* m_Mask;
	QImage m_MaskImage;
};
