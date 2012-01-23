#ifndef ICORE_H
#define ICORE_H

#include <OGRE\OgreSceneManager.h>
#include <OGRE\OgreCamera.h>

#include "iState.h"
class GameObject;

class iCore
{
public:
	iCore() {};
	virtual ~iCore() {};

	virtual void needSwitchToStateId(int xStateId) = 0;
	virtual void needShutdown() = 0;

	virtual void loadGUILayout(Ogre::String xLayoutName) = 0;
	virtual void unloadGUILayout() = 0;
	virtual void addButtonDelegate(Ogre::String xButtonName, iState *xState) = 0;

	virtual GameObject* addPlayer(Ogre::Vector2 xPos) = 0;
	virtual GameObject* addEnemy(Ogre::Vector2 xPos) = 0;
	virtual GameObject* addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination) = 0;

	virtual Ogre::SceneManager* getSceneManager() = 0;
	virtual Ogre::Camera* getCamera() = 0;
};

#endif
