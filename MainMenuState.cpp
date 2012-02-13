#include "MainMenuState.h"

MainMenuState::MainMenuState(iCore *xCore)
{
	mCore = xCore;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::prepareState()
{
	mCore->loadGUILayout("MainMenu.layout");
	mCore->addButtonDelegate("NewGameButton", this);
	mCore->addButtonDelegate("ExitButton", this);
}

void MainMenuState::enter()
{

}

void MainMenuState::exit()
{
	mCore->unloadGUILayout();
}

void MainMenuState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void MainMenuState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	if(xSender->getUserString("ButtonType") == "NewGame")
	{
		mCore->needSwitchToStateId(1);
		return;
	}

	if(xSender->getUserString("ButtonType") == "Exit")
	{
		mCore->needShutdown();
		return;
	}
}
