#ifndef ICORE_H
#define ICORE_H

#include <OGRE\OgreSceneManager.h>
#include <OGRE\OgreCamera.h>
#include <MyGUI.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <string>

#include "iState.h"

class GameObject;

class iCore
{
public:
	iCore() {};
	virtual ~iCore() {};

	virtual void needSwitchToStateId(int xStateId, bool xShowLoadState = false) = 0;
	virtual void stateLoadProgress(int xProgressValue, std::string xText) = 0;
	virtual void needShutdown() = 0;

	virtual Ogre::SceneManager* getSceneManager() = 0;
	virtual Ogre::Camera* getCamera() = 0;
	virtual	MyGUI::Gui* getGui() = 0;
	virtual OgreBulletDynamics::DynamicsWorld* getDynamicsWorld() = 0;
};

#endif
