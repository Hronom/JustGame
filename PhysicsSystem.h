#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "iMainListener.h"

#include "OgreBulletDynamicsRigidBody.h"
#include "Ogre.h"

class PhysicsSystem
{
private:
	iMainListener *mMainListener;

	OgreBulletDynamics::DynamicsWorld *mDynamicsWorld;   // OgreBullet World
	OgreBulletCollisions::DebugDrawer *mDebugDrawer;

public: 
	PhysicsSystem(iMainListener *xMainListener);

	void init(Ogre::SceneManager *xSceneManager);
};

#endif
