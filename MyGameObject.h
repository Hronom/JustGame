#ifndef MYGAMEOBJECT_H
#define MYGAMEOBJECT_H

#define BIT(x) (1<<(x))
enum CollisionGroups 
{
	EMPTY_GROUP = 0,
    PLAYER_GROUP = BIT(0), //<Collide with PLAYER
    ENEMY_GROUP = BIT(1), //<Collide with ENEMY
	BULLET_GROUP = BIT(2) //<Collide with BULLET
};

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include <MainSystem.h>
#include <MyMotionState.h>

#include "IGameObjectsListener.h"

class MyGameObject
{
protected:
	IGameObjectsListener *mGameObjectsListener;

	Ogre::String mObjectName;
	short mObjectCollideWith;
	int mHealthCount;
	int mMakeDamage;
	Ogre::Real mMoveSpeed;
	Ogre::Vector3 mMoveDirection;
	Ogre::Vector2 mDestinationDot;

	// Graph
	Ogre::Entity *mEntity;
	Ogre::SceneNode *mSceneNode;
	
	// Phys
	btCollisionShape *mCollisionShape;
	btRigidBody *mRigidBody;
	JGC::Physics::MyMotionState *mMyMotionState;

	bool mShoot;
	Ogre::Real mShootDelay;
	Ogre::Real mTimeSinceLastShot;
	bool mNeedDelete;

public:
	MyGameObject(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith);
	virtual ~MyGameObject();

	virtual void update(const Ogre::FrameEvent& evt);

	virtual Ogre::String getObjectName();
	virtual int getCurrentHealth();
	virtual int getDamage();
	virtual void makeDamage(int xDamage);
	
	virtual Ogre::Vector2 getCurrentPos();
	virtual bool isNeedDelete();

	virtual void moveUp(bool doMove);
	virtual void moveDown(bool doMove);
	virtual void moveRight(bool doMove);
	virtual void moveLeft(bool doMove);
	virtual void rotateTo(Ogre::Vector2 xDestinationDot);
	virtual void shoot(bool doShoot);
};

#endif