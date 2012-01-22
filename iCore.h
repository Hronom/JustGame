#ifndef ICORE_H
#define ICORE_H

#include "iState.h"
#include "iControlled.h"

#include <OGRE\OgreSceneManager.h>
#include <OGRE\OgreCamera.h>

class iCore
{
public:
	iCore() {};
	virtual ~iCore() {};

	virtual void needSwitchToStateId(int xStateId) = 0;
	virtual void needShutdown() = 0;

	virtual void loadGUILayout(std::string xLayoutName) = 0;
	virtual void unloadGUILayout() = 0;
	virtual void addButtonDelegate(std::string xButtonName, iState *xState) = 0;

	virtual iControlled* addPlayer(Ogre::Vector2 xPos) = 0;
	virtual void addEnemy(Ogre::Vector2 xPos) = 0;
	virtual void addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination) = 0;

	virtual Ogre::SceneManager* getSceneManager() = 0;
	virtual Ogre::Camera* getCamera() = 0;
};

#endif
