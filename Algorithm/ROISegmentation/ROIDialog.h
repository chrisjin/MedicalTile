#ifndef ROIDIALOG_H
#define ROIDIALOG_H

#include <QDialog>
#include"amyPure.h"
class amyCube;
class amyROILing;
extern template class BASIC_INTERFACE amyInput<amyCube*>;
class ROIDialog : public QDialog,public amyInput<amyCube*>
{
	Q_OBJECT

public:
	ROIDialog(QWidget *parent=0);
	~ROIDialog();
	void InitInput();
	QRect GetRect();
private:
	amyROILing* m_Ling;
};

#endif // ROIDIALOG_H
