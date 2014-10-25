
#include <QtGui/QApplication>
#include <QtGui\qtableview.h>
#include"amyCanvas.h"
#include"amyCubeLing.h"
#include"amyPatientModel.h"
#include"QAMYWindow.h"
#include"amyVariableManager.h"
//#include"QAMYVariableView.h"
#include<qscrollarea>
#include<QGridLayout>
#include<QLabel>
#include"amyVariableArea.h"
//#include"amyVariableWidget.h"
#include"amyAlgorithmManager.h"
#include"QAMYCuisineWindow.h"
#include"amySplashScreen.h"
#include"amyXMLAlgorithm.h"
#include<Windows.h>
#include<QTextCodec>
#include"amyGrid2DViewer.h"
#include"amyMPRViewer.h"
#define A_M(x) x
int main(int argc, char *argv[])
{
	//Q_INIT_RESOURCE(GUICraft);
	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gbk"));
	qApp->setStyleSheet("QWidget{border-width: 10px;border-style: solid;border-color: yellow");
	a.setApplicationName("test"); 
    a.setOrganizationName("myorg");
    a.setOrganizationDomain("myorg.com");
	//amyXMLAlgorithm* aa=new amyXMLAlgorithm(0);
	//aa->LoadXML("Test.algo");
	
	
	amySplashScreen::GetInstance()->show();
	amyAlgorithmManager::GetInstance()->LoadAlgorithm();
	QAMYWindow w;
	QAMYCuisineWindow cw;
	//amyMPRViewer mw;
	amySplashScreen::GetInstance()->finish(&cw);
	w.show();
	//mw.show();
	cw.show(); 
	return a.exec();
}
