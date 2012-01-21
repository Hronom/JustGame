#ifndef STATESMANAGER_H
#define STATESMANAGER_H

#include "iState.h"
#include "iCore.h"

class StateManager
{
private:
	std::map<int, iState*> mStatesMap;

	iState *mCurrentState;

public:
	StateManager(iCore *xCore);
	~StateManager();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	void switchToStateId(int xStateId);
};

#endif

