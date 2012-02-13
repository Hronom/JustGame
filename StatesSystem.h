#ifndef STATESSYSTEM_H
#define STATESSYSTEM_H

#include "iSystemsListener.h"
#include "iCore.h"
#include "iLoadState.h"
#include "iState.h"

class StatesSystem
{
private:
	iSystemsListener *mMainListener;

	iLoadState *mLoadState;
	iState *mCurrentState;
	std::map<int, iState*> mStatesMap;

public:
	StatesSystem(iSystemsListener *xMainListener);
	~StatesSystem();

	bool init();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void injectMouseMoved(const OIS::MouseEvent& e);
	virtual void injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void injectKeyPressed(const OIS::KeyEvent& e);
	virtual void injectKeyReleased(const OIS::KeyEvent& e);
	virtual void injectStateLoadProgress(int xProgressValue, std::string xText);

	void setLoadState(iLoadState *xLoadState);
	void addNormalState(int xNumber, iState *xState);
	void switchToState(int xStateId, bool xShowLoadState = false);
};

#endif
