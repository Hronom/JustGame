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

	//-------------------------------------------------------------
	// iCore
	//-------------------------------------------------------------
	virtual void needSwitchToStateId(int xStateId);
	virtual void needShutdown();

	virtual void loadGUILayout(std::string xLayoutName);
	virtual void unloadGUILayout();
	virtual void addButtonDelegate(std::string xButtonName, iState *xState);

	virtual void addPlayer(Ogre::Vector3 xPos);
	virtual void addEnemy(Ogre::Vector3 xPos);

	virtual void movePlayerUp();
	virtual void movePlayerDown();
	virtual void movePlayerLeft();
	virtual void movePlayerRight();
	virtual void playerShoot();
};

#endif

