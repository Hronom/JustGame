#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>
#include <MainSystem.h>
#include <SoundSystem.h>
#include <SoundListener.h>
#include <SoundSource.h>
#include "MyGameObject.h"

class Enemy: public MyGameObject
{
private:
	Ogre::ManualObject *mManualObject;
	JGC::SoundSource *mSoundSource;

	Ogre::Real mTimeBeforeDelete;

public:
	Enemy(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Enemy();

	virtual void update(const float& xTimeSinceLastFrame);

private:
	void rotateEnemy(Ogre::Real xTimeSinceLastFrame);
	void moveEnemy(Ogre::Real xTimeSinceLastFrame);
	void enemyShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif
