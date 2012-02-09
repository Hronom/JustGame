#include "MainMenuState.h"

MainMenuState::MainMenuState(iCore *xCore)
{
	mCore = xCore;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::enter()
{
	mCore->loadGUILayout("MainMenu.layout");
	mCore->addButtonDelegate("NewGameButton", this);
	mCore->addButtonDelegate("ExitButton", this);
}

void MainMenuState::exit()
{
	mCore->unloadGUILayout();
}

void MainMenuState::needUpdate(const Ogre::FrameEvent& evt)
{
}

void MainMenuState::mouseMoved(const OIS::MouseEvent& e)
{
}

void MainMenuState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void MainMenuState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void MainMenuState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void MainMenuState::keyReleased(const OIS::KeyEvent& e)
{
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
