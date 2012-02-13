#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "iSystemsListener.h"

#include "OgreBulletDynamicsRigidBody.h"
#include "Ogre.h"

class PhysicsSystem
{
private:
	iSystemsListener *mMainListener;

	OgreBulletDynamics::DynamicsWorld *mDynamicsWorld;   // OgreBullet World
	OgreBulletCollisions::DebugDrawer *mDebugDrawer;

public: 
	PhysicsSystem(iSystemsListener *xMainListener);
	~PhysicsSystem();

	void init(Ogre::SceneManager *xSceneManager);

	void needUpdate(const Ogre::FrameEvent& evt);

	OgreBulletDynamics::DynamicsWorld* getDynamicsWorld();
};

#endif
