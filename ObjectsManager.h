#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include <OGRE\OgreSceneManager.h>
#include <sstream>

#include "iCore.h"
#include "iGameObject.h"
#include "iControlled.h"
#include "Player.h"
//#include "Enemy.h"
#include "Bullet.h"


class ObjectsManager
{
private:
	int mBulletsCount;
	Ogre::SceneManager *mSceneManager;

	iCore *mCore;
	Player *mPlayer;

	std::vector<iGameObject*> mGameObjects;

public:
	ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager);
	~ObjectsManager();

	virtual void needUpdate(const Ogre::FrameEvent& evt);

	iControlled* addPlayer(Ogre::Vector2 xPos);
	void addEnemy(Ogre::Vector2 xPos);
	void addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination) ;
};

#endif

