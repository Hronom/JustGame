#include <MainSystem.h>
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

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}