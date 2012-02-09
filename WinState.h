#ifndef WINSTATE_H
#define WINSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include "iCore.h"
#include "iState.h"

class WinState: public iState
{
private:
	iCore *mCore;

public:
	WinState(iCore *xCore);
	~WinState();

	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	virtual void buttonClicked(MyGUI::WidgetPtr xSender);
};

#endif

