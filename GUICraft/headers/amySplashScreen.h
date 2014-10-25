#ifndef AMYSPLASHSCREEN_H
#define AMYSPLASHSCREEN_H
#include"GuiMacro.h"
#include <QSplashScreen>
#include"amyPure.h"
class GUI_INTERFACE amySplashScreen : public QSplashScreen
{
	Q_OBJECT
	DEFINE_SINGLETON(amySplashScreen)
public:
	amySplashScreen(QWidget *parent=0);
	~amySplashScreen();

private:
	
};

#endif // AMYSPLASHSCREEN_H
