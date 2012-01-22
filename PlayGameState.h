#ifndef PLAYGAMESTATE_H
#define PLAYGAMESTATE_H

#include <Ogre.h>
#include <OGRE\OgreRay.h>
#include <MyGUI.h>
#include <OIS\OIS.h>

#include "iCore.h"
#include "iState.h"

class PlayGameState: public iState
{
private:
	iCore *mCore;
	iControlled *mControlledPlayer;

public:
	PlayGameState(iCore *xCore);
	~PlayGameState();

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

