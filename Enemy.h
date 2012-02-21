#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>
#include <MainSystem.h>
#include "MyGameObject.h"

class Enemy: public MyGameObject
{
private:
	Ogre::ManualObject *mManualObject;

	Ogre::Real mTimeBeforeDelete;

public:
	Enemy(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Enemy();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotateEnemy(Ogre::Real xTimeSinceLastFrame);
	void moveEnemy(Ogre::Real xTimeSinceLastFrame);
	void enemyShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif
