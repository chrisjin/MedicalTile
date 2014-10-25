#pragma once
#include<QPushButton>
class amyColorButton:public QPushButton
{
	Q_OBJECT
public:
	amyColorButton(QWidget* p=0);
	void SetColor(QColor c);
	QColor GetColor();
public slots:
	void OnClick();
signals:
	void s_colorchanged();
private:
	QColor m_Color;
};