#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "iCore.h"
#include "GameObject.h"

class Player: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;
	Ogre::Entity *mEntity;

	OgreBulletCollisions::SphereCollisionShape *mSphereShape;
	OgreBulletDynamics::RigidBody *mRigidBody;

public:
	Player(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos);
	~Player();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotatePlayer(Ogre::Real xTimeSinceLastFrame);
	void movePlayer(Ogre::Real xTimeSinceLastFrame);
	void playerShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif