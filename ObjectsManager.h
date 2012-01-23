#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include <OGRE\OgreSceneManager.h>

#include "iCore.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


class ObjectsManager
{
private:
	int mEnemyCount;
	int mBulletsCount;
	Ogre::SceneManager *mSceneManager;

	iCore *mCore;
	Player *mPlayer;

	std::vector<GameObject*> mGameObjects;

public:
	ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager);
	~ObjectsManager();

	virtual void needUpdate(const Ogre::FrameEvent& evt);

	GameObject* addPlayer(Ogre::Vector2 xPos);
	GameObject* addEnemy(Ogre::Vector2 xPos);
	GameObject* addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination) ;
};

#endif

