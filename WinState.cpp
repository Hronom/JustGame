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

void WinState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void WinState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}
