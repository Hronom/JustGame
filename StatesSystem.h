#ifndef STATESSYSTEM_H
#define STATESSYSTEM_H

#include "ISystemsListener.h"
#include "ICore.h"
#include "ILoadScreen.h"
#include "IState.h"

class StatesSystem
{
private:
	ISystemsListener *mMainListener;

	ILoadScreen *mLoadState;
	IState *mCurrentState;
	std::map<int, IState*> mStatesMap;

public:
	StatesSystem(ISystemsListener *xMainListener);
	~StatesSystem();

	bool init();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void injectMouseMoved(const OIS::MouseEvent& e);
	virtual void injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void injectKeyPressed(const OIS::KeyEvent& e);
	virtual void injectKeyReleased(const OIS::KeyEvent& e);
	virtual void injectStateLoadProgress(int xProgressValue, std::string xText);

	void setLoadState(ILoadScreen *xLoadState);
	void addNormalState(int xNumber, IState *xState);
	void switchToState(int xStateId, bool xShowLoadState = false);
};

#endif
