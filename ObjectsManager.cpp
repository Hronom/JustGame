#include "ObjectsManager.h"


ObjectsManager::ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager)
{
	mBulletsCount = 0;

	mSceneManager = xSceneManager;
	mCore = xCore;
}


ObjectsManager::~ObjectsManager()
{
}

void ObjectsManager::needUpdate(const Ogre::FrameEvent& evt)
{
	for(int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->update(evt);

	}
}

iControlled* ObjectsManager::addPlayer(Ogre::Vector2 xPos)
{
	mPlayer = new Player(mCore, xPos);
	mGameObjects.push_back(mPlayer);

	return mPlayer;
}

void ObjectsManager::addEnemy(Ogre::Vector2 xPos)
{
}

void ObjectsManager::addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mBulletsCount++;
	std::string xBulletName;
	std::stringstream xOut;

	xOut << "Bullet" << mBulletsCount;
	xBulletName = xOut.str();

	Bullet *xBullet;
	xBullet = new Bullet(mCore, xBulletName, xPos, xDestination);
	mGameObjects.push_back(xBullet);
}