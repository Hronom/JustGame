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

iControlled* ObjectsManager::addPlayer(Ogre::Vector2 xPos)
{
	mPlayer = new Player(mSceneManager, xPos);
	mGameObjects.push_back(mPlayer);

	return mPlayer;
}

void ObjectsManager::addEnemy(Ogre::Vector2 xPos)
{
}

void ObjectsManager::addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{

}