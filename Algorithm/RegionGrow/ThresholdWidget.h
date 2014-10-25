#pragma once
#include<QWidget>
#include"amyPure.h"
#include"amyKeeper.h"
#include<QDialog>
class amyMaskLing;
class amyCube;
class amyCanvas;
class ThresholdWidget;
class QScrollBar;
class WDialog:public QDialog
{
public:
	WDialog(QWidget*p=0);
public:
	ThresholdWidget* m_W;
};
//extern  class  DICOM_INTERFACE amyCube;
//extern template class  DICOM_INTERFACE amyKeeper<amyCube>;
//extern template class DICOM_INTERFACE amyInput<amyKeeper<amyCube>>;
class ThresholdWidget:public QWidget,public amyInput<amyKeeper<amyCube>>
{
	Q_OBJECT
public:
	ThresholdWidget(QWidget* p=0);
	void InitInput();
	amyKeeper<amyCube> GetMask(){return m_Mask;}
	void UpdateMask(int above,int below);
public slots:
	void UpdateAbove(int above);
	void UpdateBelow(int below);
	void UpdateSlice(int slice);
	
	void Confirm();
private:
	amyKeeper<amyCube> m_Mask;
	amyMaskLing* m_MaskLing;
	amyCanvas*   m_Canvas;
	QScrollBar*  m_AboveSlider;
	QScrollBar*  m_BelowSlider;
	int m_Max;
	int m_Min;
	int m_Slice;
	//int m_Threshold;

	int m_ThresholdAbove;
	int m_ThresholdBelow;
};