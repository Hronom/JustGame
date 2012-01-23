#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <MyGUI.h>
#include <OgreSceneManager.h>

#include "iCore.h"
#include "iMainListener.h"
#include "GUIManager.h"
#include "ObjectsManager.h"
#include "StateManager.h"
#include "GameObject.h"

class MainManager: public iMainListener, public iCore
{
private:
	bool mNeedShutdown;
	GUIManager *mGUIManager;
	ObjectsManager *mObjectsManager;
	StateManager *mStateManager;

	Ogre::SceneManager *mSceneManager;
	Ogre::Camera *mCamera;

public:
	MainManager(MyGUI::Gui *xMyGUI, Ogre::SceneManager *xSceneManager, Ogre::Camera* xCamera);
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

	virtual void loadGUILayout(Ogre::String xLayoutName);
	virtual void unloadGUILayout();
	virtual void addButtonDelegate(Ogre::String xButtonName, iState *xState);

	virtual GameObject* addPlayer(Ogre::Vector2 xPos);
	virtual GameObject* addEnemy(Ogre::Vector2 xPos);
	virtual GameObject* addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination);

	virtual Ogre::SceneManager* getSceneManager();
	virtual Ogre::Camera* getCamera();
};

#endif

