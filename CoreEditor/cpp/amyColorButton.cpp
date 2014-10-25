#include"amyColorButton.h"
#include<QColorDialog>
amyColorButton::amyColorButton(QWidget* p):QPushButton(p)
{
	m_Color=Qt::black;
	connect(this,SIGNAL(clicked()),this,SLOT(OnClick()));
}

void amyColorButton::OnClick()
{
	QColor init=GetColor();
	SetColor(QColorDialog::getColor(init));
}
void amyColorButton::SetColor(QColor c)
{
	m_Color=c;
	QPixmap p(64,64);
	p.fill(c);
	setIcon(QIcon(p));
	emit s_colorchanged();
}
QColor amyColorButton::GetColor()
{
	return m_Color;
}