#include "GameObject.h"

#include "iCore.h"
#include "iGameObjectsListener.h"

GameObject::GameObject(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectType)
{
	mCore = xCore;
	mGameObjectsListener = xGameObjectsListener;

	mObjectName = xObjectName;
	mObjectType = xObjectType;
	mHealthCount = 0;
	mDamage = 0;
	mMoveSpeed = 0;

	mObjectNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode(xObjectName+"_Node");
	mObjectRadius = 0;
	mMoveDirection = Ogre::Vector3::ZERO;
	mDestinationDot = Ogre::Vector2::ZERO;

	mCanDoShot = false;
	mShootDelay = 0;
	mTimeAfterLastShoot = mShootDelay;

	mNeedDelete = false;
}

GameObject::~GameObject()
{
	mObjectNode->removeAndDestroyAllChildren();
	mCore->getSceneManager()->destroySceneNode(mObjectNode->getName());
}

void GameObject::update(const Ogre::FrameEvent& evt)
{

}

Ogre::String GameObject::getObjectName()
{
	return mObjectName; 
}

int GameObject::getCurrentHealth()
{
	return mHealthCount;
}

int GameObject::getDamage()
{
	return mDamage;
}

void GameObject::doDamage(int xDamage)
{
	mHealthCount -= xDamage;
}

Ogre::Vector2 GameObject::getCurrentPos()
{
	Ogre::Vector3 xVector3Pos;
	Ogre::Vector2 xVector2Pos;

	xVector3Pos = mObjectNode->getPosition();

	xVector2Pos.x = xVector3Pos.x;
	xVector2Pos.y = xVector3Pos.y;

	return xVector2Pos;
}

float GameObject::getObjectRadius()
{
	return mObjectRadius;
}

bool GameObject::isNeedDelete()
{
	return mNeedDelete;
}

void GameObject::moveUp(bool doMove)
{
	if(doMove == true)
		mMoveDirection.x = 1;
	else 
		mMoveDirection.x = 0;
}

void GameObject::moveDown(bool doMove)
{
	if(doMove == true)
		mMoveDirection.x = -1;
	else 
		mMoveDirection.x = 0;
}

void GameObject::moveRight(bool doMove)
{
	if(doMove == true)
		mMoveDirection.y = -1;
	else 
		mMoveDirection.y = 0;
}

void GameObject::moveLeft(bool doMove)
{
	if(doMove == true)
		mMoveDirection.y = 1;
	else 
		mMoveDirection.y = 0;
}

void GameObject::rotateTo(Ogre::Vector2 xDestinationDot)
{
	mDestinationDot = xDestinationDot;
}

void GameObject::shoot(bool doShoot)
{
	mCanDoShot = doShoot;
}
