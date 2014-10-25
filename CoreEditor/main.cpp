#include "coreeditor.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CoreEditor w;
	w.show();
	return a.exec();
}
