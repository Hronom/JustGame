#include "LoseState.h"

LoseState::LoseState(iCore *xCore)
{
	mCore = xCore;
}

LoseState::~LoseState()
{
}

void LoseState::prepareState()
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

void LoseState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void LoseState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}

