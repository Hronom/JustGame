#include "WinState.h"

WinState::WinState(iCore *xCore)
{
	mCore = xCore;
}

WinState::~WinState()
{
}

void WinState::enter()
{
	mCore->loadGUILayout("WinMenu.layout");
	mCore->addButtonDelegate("OkButton", this);
}

void WinState::exit()
{
	mCore->unloadGUILayout();
}

void WinState::needUpdate(const Ogre::FrameEvent& evt)
{
}

void WinState::mouseMoved(const OIS::MouseEvent& e)
{
}

void WinState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void WinState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void WinState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void WinState::keyReleased(const OIS::KeyEvent& e)
{
}

void WinState::buttonClick(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}
