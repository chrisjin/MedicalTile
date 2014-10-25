#ifndef TESTRC_H
#define TESTRC_H

#include <QtGui/QMainWindow>
#include "ui_testrc.h"

class TestRc : public QMainWindow
{
	Q_OBJECT

public:
	TestRc(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TestRc();

private:
	Ui::TestRcClass ui;
};

#endif // TESTRC_H
