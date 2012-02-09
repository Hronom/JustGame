#ifndef STATESSYSTEM_H
#define STATESSYSTEM_H

#include "iState.h"
#include "iCore.h"

class StatesSystem
{
private:
	iState *mCurrentState;
	std::map<int, iState*> mStatesMap;

public:
	StatesSystem();
	~StatesSystem();

	bool init();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void injectMouseMoved(const OIS::MouseEvent& e);
	virtual void injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void injectKeyPressed(const OIS::KeyEvent& e);
	virtual void injectKeyReleased(const OIS::KeyEvent& e);

	void addState(int xNumber, iState *xState);
	void switchToState(int xStateId);
};

#endif
