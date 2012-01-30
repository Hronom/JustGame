#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>

#include "OgreBulletDynamicsRigidBody.h"

#include <OIS\OIS.h>

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

#include "MainManager.h"
#include "GameWindowEventListener.h"
#include "GameFrameListener.h"
#include "GameMouseListener.h"
#include "GameKeyListener.h"

class MainClass
{
private:
	Ogre::String mOgreCfg;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::String mLogFileName;

	Ogre::Root *mRoot;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::Camera* mCamera; 

	OgreBulletDynamics::DynamicsWorld *mDynamicsWorld;   // OgreBullet World
	OgreBulletCollisions::DebugDrawer *mDebugDrawer;

	OIS::InputManager *mInputManager;
	OIS::Keyboard *mKeyboard;
	OIS::Mouse *mMouse;

	MyGUI::OgrePlatform *mPlatform;
	MyGUI::Gui *mMyGUI;

	MainManager *mMainManager;
	GameWindowEventListener *mGameWindowEventListener;
	GameFrameListener *mGameFrameListener;
	GameMouseListener *mGameMouseListener;
	GameKeyListener *mGameKeyListener;

public:
	MainClass();
	virtual ~MainClass();
	bool run();

private:
	bool initConfig();
	void createWindow();
	void loadResources();
	void createScene();
	void initPhysics();
	void initMyGUI();
	void initOIS();
	void initListeners();
};

#endif