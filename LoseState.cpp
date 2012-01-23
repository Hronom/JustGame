#include "LoseState.h"

LoseState::LoseState(iCore *xCore)
{
	mCore = xCore;
}

LoseState::~LoseState()
{
}

void LoseState::enter()
{
	mCore->loadGUILayout("LoseMenu.layout");
	mCore->addButtonDelegate("OkButton", this);
}

void LoseState::exit()
{
	mCore->unloadGUILayout();
}

void LoseState::needUpdate(const Ogre::FrameEvent& evt)
{
}

void LoseState::mouseMoved(const OIS::MouseEvent& e)
{
}

void LoseState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void LoseState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void LoseState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void LoseState::keyReleased(const OIS::KeyEvent& e)
{
}

void LoseState::buttonClick(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}

