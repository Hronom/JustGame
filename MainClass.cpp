#include "MainClass.h"

#include "LoadScreen.h"
#include "SplashState.h"
#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"

MainClass::MainClass()
{
	JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

	LoadScreen *xLoadState = new LoadScreen();
	JGC::MainSystem::instance()->setLoadState(xLoadState);

	SplashState *xSplashState = new SplashState();
	JGC::MainSystem::instance()->addNormalState("SplashState", xSplashState);

	MainMenuState *xMainMenuState = new MainMenuState();
	JGC::MainSystem::instance()->addNormalState("MainMenuState", xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState();
	JGC::MainSystem::instance()->addNormalState("PlayGameState", xPlayGameState);
	
	WinState *xWinState = new WinState();
	JGC::MainSystem::instance()->addNormalState("WinState", xWinState);
	
	LoseState *xLoseState = new LoseState();
	JGC::MainSystem::instance()->addNormalState("LoseState", xLoseState);

	JGC::MainSystem::instance()->needSwitchToState("SplashState");
}


MainClass::~MainClass()
{
	JGC::MainSystem::shutdown();
}

void MainClass::start()
{
	JGC::MainSystem::instance()->run();
}
