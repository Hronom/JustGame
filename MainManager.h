#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include "iMainListener.h"
#include "GUIManager.h"
#include "ObjectsManager.h"
#include "StateManager.h"
#include "iCore.h"

#include <MyGUI.h>
#include <OgreSceneManager.h>

class MainManager: public iMainListener, public iCore
{
private:
	bool mNeedShutdown;
	GUIManager *mGUIManager;
	ObjectsManager *mObjectsManager;
	StateManager *mStateManager;

public:
	MainManager(MyGUI::Gui *xMyGUI, Ogre::SceneManager *xSceneManager);
	~MainManager();

	virtual bool needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	virtual void needShutdown();
};

#endif

