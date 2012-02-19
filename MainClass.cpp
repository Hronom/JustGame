#include "MainClass.h"

#include "LoadScreen.h"
#include "SplashState.h"
#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"

MainClass::MainClass()
{
	mMainSystem = new MainSystem("Ogre.cfg",
		"Plugins.cfg",
		"../Media/Resources.cfg",
		"Ogre.log", "MyGUI.log");

	mMainSystem->init();

	LoadScreen *xLoadState = new LoadScreen(mMainSystem);
	mMainSystem->setLoadState(xLoadState);

	SplashState *xSplashState = new SplashState(mMainSystem);
	mMainSystem->addNormalState("SplashState", xSplashState);

	MainMenuState *xMainMenuState = new MainMenuState(mMainSystem);
	mMainSystem->addNormalState("MainMenuState", xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState(mMainSystem);
	mMainSystem->addNormalState("PlayGameState", xPlayGameState);
	
	WinState *xWinState = new WinState(mMainSystem);
	mMainSystem->addNormalState("WinState", xWinState);
	
	LoseState *xLoseState = new LoseState(mMainSystem);
	mMainSystem->addNormalState("LoseState", xLoseState);

	mMainSystem->needSwitchToState("SplashState");
}


MainClass::~MainClass()
{
	delete mMainSystem;
	mMainSystem=0;
}

void MainClass::start()
{
	mMainSystem->run();
}
