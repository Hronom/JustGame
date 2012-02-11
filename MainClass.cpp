#include "MainClass.h"

#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"

MainClass::MainClass()
{
	mMainSystem = new MainSystem();

	mMainSystem->init();

	MainMenuState *xMainMenuState = new MainMenuState(mMainSystem);
	mMainSystem->addState(0, xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState(mMainSystem);
	mMainSystem->addState(1, xPlayGameState);
	
	WinState *xWinState = new WinState(mMainSystem);
	mMainSystem->addState(2, xWinState);
	
	LoseState *xLoseState = new LoseState(mMainSystem);
	mMainSystem->addState(3, xLoseState);
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
