#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include <OGRE\OgreSceneManager.h>

#include "iCore.h"
#include "iGameObject.h"
#include "Player.h"
//#include "Enemy.h"

class ObjectsManager
{
private:
	Ogre::SceneManager *mSceneManager;

	iCore *mCore;
	Player *mPlayer;

	std::vector<iGameObject*> mGameObjects;

public:
	ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager);
	~ObjectsManager();

	virtual void needUpdate(const Ogre::FrameEvent& evt);

	void addPlayer(Ogre::Vector3 xPos);
	void addEnemy(Ogre::Vector3 xPos);

	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();
	void playerShoot();
};

#endif

