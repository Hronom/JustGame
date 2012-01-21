#include "StateManager.h"

#include "MainMenuState.h"


StateManager::StateManager(iCore *xCore, GUIManager *xGUIManager)
{
	mCurrentState = new MainMenuState(xCore, xGUIManager);
	mCurrentState->enter();
}


StateManager::~StateManager()
{

}