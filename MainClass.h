#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "MainListener.h"

class MainClass
{
private:
	Ogre::Root* mRoot;
	Ogre::String mOgreCfg;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::String mLogFileName;

	Ogre::RenderWindow* mWindow;

	Ogre::SceneManager* mSceneManager;

	// OIS Input devices
	OIS::InputManager* mInputManager;

	MainListener *mMainListener;

public:
	MainClass();
	virtual ~MainClass();
	bool start();

private:
	bool initRoot();
	void initResources();
	void initScene();
	void initOIS();
};

#endif