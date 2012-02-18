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
	mMainSystem->addNormalState(-1, xSplashState);

	MainMenuState *xMainMenuState = new MainMenuState(mMainSystem);
	mMainSystem->addNormalState(0, xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState(mMainSystem);
	mMainSystem->addNormalState(1, xPlayGameState);
	
	WinState *xWinState = new WinState(mMainSystem);
	mMainSystem->addNormalState(2, xWinState);
	
	LoseState *xLoseState = new LoseState(mMainSystem);
	mMainSystem->addNormalState(3, xLoseState);

	mMainSystem->needSwitchToStateId(-1);
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
