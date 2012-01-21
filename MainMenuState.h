#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include "iState.h"
#include "GUIManager.h"
#include "iCore.h"

class MainMenuState: public iState
{
private:
	iCore *mCore;
	GUIManager *mGUIManager;
public:
	MainMenuState(iCore *xCore, GUIManager *xGUIManager);
	~MainMenuState();

	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	virtual void buttonClick(MyGUI::WidgetPtr xSender);
};

#endif

