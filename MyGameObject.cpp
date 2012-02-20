#include "MyGameObject.h"

MyGameObject::MyGameObject(ICore *xCore, IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith)
{
	mCore = xCore;
	mGameObjectsListener = xGameObjectsListener;

	mObjectName = xObjectName;
	mObjectCollideWith = xObjectCollideWith;
	mHealthCount = 0;
	mMakeDamage = 0;
	mMoveSpeed = 0;
	mMoveDirection = Ogre::Vector3::ZERO;
	mDestinationDot = Ogre::Vector2::ZERO;

	// Graph
	mEntity = 0;
	mSceneNode = 0;
	
	// Phys
	mCollisionShape = 0;
	mRigidBody = 0;

	mShoot = false;
	mShootDelay = 0;
	mTimeSinceLastShot = mShootDelay;
	mNeedDelete = false;
}

MyGameObject::~MyGameObject()
{
	if(mRigidBody != 0)
	{
		mCore->getDynamicsWorld()->getBulletDynamicsWorld()->removeRigidBody(mRigidBody->getBulletRigidBody());
		delete mRigidBody->getBulletRigidBody()->getMotionState();
		delete mRigidBody->getBulletRigidBody();
	}

	if(mCollisionShape != 0)
		delete mCollisionShape;

	if(mEntity != 0) 
		mCore->getSceneManager()->destroyEntity(mEntity);

	if(mSceneNode != 0)
	{
		mSceneNode->removeAndDestroyAllChildren();
		mCore->getSceneManager()->destroySceneNode(mSceneNode);
	}
}

void MyGameObject::update(const Ogre::FrameEvent& evt)
{

}

Ogre::String MyGameObject::getObjectName()
{
	return mObjectName; 
}

int MyGameObject::getCurrentHealth()
{
	return mHealthCount;
}

int MyGameObject::getDamage()
{
	return mMakeDamage;
}

void MyGameObject::makeDamage(int xDamage)
{
	mHealthCount -= xDamage;
}

Ogre::Vector2 MyGameObject::getCurrentPos()
{
	Ogre::Vector3 xVector3Pos;
	Ogre::Vector2 xVector2Pos;

	xVector3Pos = mSceneNode->getPosition();

	xVector2Pos.x = xVector3Pos.x;
	xVector2Pos.y = xVector3Pos.y;

	return xVector2Pos;
}

bool MyGameObject::isNeedDelete()
{
	return mNeedDelete;
}

void MyGameObject::moveUp(bool doMove)
{
	if(doMove == true)
		mMoveDirection.x = 1;
	else 
		mMoveDirection.x = 0;
}

void MyGameObject::moveDown(bool doMove)
{
	if(doMove == true)
		mMoveDirection.x = -1;
	else 
		mMoveDirection.x = 0;
}

void MyGameObject::moveRight(bool doMove)
{
	if(doMove == true)
		mMoveDirection.y = -1;
	else 
		mMoveDirection.y = 0;
}

void MyGameObject::moveLeft(bool doMove)
{
	if(doMove == true)
		mMoveDirection.y = 1;
	else 
		mMoveDirection.y = 0;
}

void MyGameObject::rotateTo(Ogre::Vector2 xDestinationDot)
{
	mDestinationDot = xDestinationDot;
}

void MyGameObject::shoot(bool doShoot)
{
	mShoot = doShoot;
}
