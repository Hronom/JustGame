#include <MainSystem.h>
#include <StatesSystem.h>
#include "LoadScreen.h"
#include "SplashState.h"
#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

	LoadScreen *xLoadState = new LoadScreen();
	JGC::StatesSystem::instance()->setLoadState(xLoadState);

	SplashState *xSplashState = new SplashState();
	JGC::StatesSystem::instance()->addNormalState("SplashState", xSplashState);

	MainMenuState *xMainMenuState = new MainMenuState();
	JGC::StatesSystem::instance()->addNormalState("MainMenuState", xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState();
	JGC::StatesSystem::instance()->addNormalState("PlayGameState", xPlayGameState);
	
	WinState *xWinState = new WinState();
	JGC::StatesSystem::instance()->addNormalState("WinState", xWinState);
	
	LoseState *xLoseState = new LoseState();
	JGC::StatesSystem::instance()->addNormalState("LoseState", xLoseState);

	JGC::StatesSystem::instance()->needSwitchToState("SplashState");

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
