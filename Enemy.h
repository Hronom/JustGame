#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>

#include "ICore.h"
#include "GameObject.h"

class Enemy: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;

	Ogre::Real mTimeBeforeDelete;

public:
	Enemy(ICore *xCore, IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Enemy();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotateEnemy(Ogre::Real xTimeSinceLastFrame);
	void moveEnemy(Ogre::Real xTimeSinceLastFrame);
	void enemyShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif
