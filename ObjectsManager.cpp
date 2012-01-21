#include "ObjectsManager.h"


ObjectsManager::ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager)
{
	mSceneManager = xSceneManager;
	mCore = xCore;

	
}


ObjectsManager::~ObjectsManager()
{
}

void ObjectsManager::needUpdate(const Ogre::FrameEvent& evt)
{
	for(int i = 0; i < mGameObjects.size(); i++)
		mGameObjects[i]->update(evt);
}

void ObjectsManager::addPlayer(Ogre::Vector3 xPos)
{
	mPlayer = new Player(mSceneManager, xPos);
	mGameObjects.push_back(mPlayer);
}

void ObjectsManager::addEnemy(Ogre::Vector3 xPos)
{
}

void ObjectsManager::movePlayerUp()
{
	mPlayer->movePlayerUp();
}

void ObjectsManager::movePlayerDown()
{
	mPlayer->movePlayerDown();
}

void ObjectsManager::movePlayerLeft()
{
	mPlayer->movePlayerLeft();
}

void ObjectsManager::movePlayerRight()
{
	mPlayer->movePlayerRight();
}

void ObjectsManager::playerShoot()
{
	mPlayer->playerShoot();
}
