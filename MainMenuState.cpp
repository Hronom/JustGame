#include "MainMenuState.h"

MainMenuState::MainMenuState(iCore *xCore, GUIManager *xGUIManager)
{
	mCore = xCore;
	mGUIManager = xGUIManager;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::enter()
{
	mGUIManager->loadLayout("sample.layout");
	mGUIManager->addButtonDelegate("MyFirstButton", this);
}

void MainMenuState::exit()
{
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
}

void MainMenuState::keyReleased(const OIS::KeyEvent& e)
{
}

void MainMenuState::buttonClick(MyGUI::WidgetPtr xSender)
{
	mCore->needShutdown();
}
