#include "testrc.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestRc w;
	w.show();
	return a.exec();
}
