#include "MainClass.h"

#include "LoadState.h"
#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"

MainClass::MainClass()
{
	mMainSystem = new MainSystem();

	mMainSystem->init();

	LoadState *xLoadState = new LoadState(mMainSystem);
	mMainSystem->setLoadState(xLoadState);

	MainMenuState *xMainMenuState = new MainMenuState(mMainSystem);
	mMainSystem->addNormalState(0, xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState(mMainSystem);
	mMainSystem->addNormalState(1, xPlayGameState);
	
	WinState *xWinState = new WinState(mMainSystem);
	mMainSystem->addNormalState(2, xWinState);
	
	LoseState *xLoseState = new LoseState(mMainSystem);
	mMainSystem->addNormalState(3, xLoseState);

	mMainSystem->needSwitchToStateId(0);
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
