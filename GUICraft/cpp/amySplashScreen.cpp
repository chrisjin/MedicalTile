#include "amySplashScreen.h"
IMPLEMENT_SINGLETON(amySplashScreen)
amySplashScreen::amySplashScreen(QWidget *parent)
	: QSplashScreen(parent)
{
	this->setPixmap(QPixmap(":/ICON/Splash"));
	setAttribute(Qt::WA_TranslucentBackground);
}

amySplashScreen::~amySplashScreen()
{

}
