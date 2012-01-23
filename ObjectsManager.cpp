#include "ObjectsManager.h"


ObjectsManager::ObjectsManager(iCore *xCore, Ogre::SceneManager *xSceneManager)
{
	mEnemyCount = 0;
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

GameObject* ObjectsManager::addPlayer(Ogre::Vector2 xPos)
{
	mPlayer = new Player(mCore, "Player", xPos);
	mGameObjects.push_back(mPlayer);

	return mPlayer;
}

GameObject* ObjectsManager::addEnemy(Ogre::Vector2 xPos)
{
	mEnemyCount++;
	Ogre::String xEnemyName;
	xEnemyName = "Enemy" + Ogre::StringConverter::toString(mEnemyCount);

	Enemy *xEnemy;
	xEnemy = new Enemy(mCore, xEnemyName, xPos);
	mGameObjects.push_back(xEnemy);

	return xEnemy;
}

GameObject* ObjectsManager::addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mBulletsCount++;
	Ogre::String xBulletName;
	xBulletName = "Bullet" + Ogre::StringConverter::toString(mBulletsCount);

	Bullet *xBullet;
	xBullet = new Bullet(mCore, xBulletName, xPos, xDestination);
	mGameObjects.push_back(xBullet);
	return xBullet;
}