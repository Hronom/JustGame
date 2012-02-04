#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>

#include "iCore.h"
#include "GameObject.h"

class Enemy: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;
	Ogre::Entity *mEntity;
	Ogre::Real mTimeBeforeDelete;

	OgreBulletCollisions::SphereCollisionShape *mSphereShape;
	OgreBulletDynamics::RigidBody *mRigidBody;

public:
	Enemy(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectType, Ogre::Vector2 xPos);
	~Enemy();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotateEnemy(Ogre::Real xTimeSinceLastFrame);
	void moveEnemy(Ogre::Real xTimeSinceLastFrame);
	void enemyShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif
