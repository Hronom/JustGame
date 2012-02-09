#include "MainSystem.h"

#include "MainMenuState.h"
#include "PlayGameState.h"
#include "WinState.h"
#include "LoseState.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	MainSystem xMainSystem;
	xMainSystem.init();

	MainMenuState *xMainMenuState = new MainMenuState(&xMainSystem);
	xMainSystem.addState(0, xMainMenuState);
	
	PlayGameState *xPlayGameState = new PlayGameState(&xMainSystem);
	xMainSystem.addState(1, xPlayGameState);
	
	WinState *xWinState = new WinState(&xMainSystem);
	xMainSystem.addState(2, xWinState);
	
	LoseState *xLoseState = new LoseState(&xMainSystem);
	xMainSystem.addState(3, xLoseState);	

	xMainSystem.run();

	return 0;
}