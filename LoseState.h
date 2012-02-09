#ifndef LOSESTATE_H
#define LOSESTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include "iCore.h"
#include "iState.h"

class LoseState: public iState
{
private:
	iCore *mCore;

public:
	LoseState(iCore *xCore);
	~LoseState();

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

