#include "GameObject.h"

#include "iCore.h"
#include "iGameObjectsListener.h"

GameObject::GameObject(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName)
{
	mCore = xCore;
	mGameObjectsListener = xGameObjectsListener;

	mObjectName = xObjectName;
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
	// MOVE
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);



	// ROTATE
	Ogre::Vector3 xDirection = Ogre::Vector3(mDestinationDot.x, mDestinationDot.y, 0) - mObjectNode->getPosition();
	xDirection.z = 0;

	Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	xSrc.z = 0;
	xSrc.normalise();

	if ((1.0f + xSrc.dotProduct(xDirection)) < 0.0001f) 
	{
		mObjectNode->roll(Ogre::Degree(180));
	}
	else
	{
		Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
		mObjectNode->rotate(xQuat);
	}



	// SHOOT!!!
	if(mCanDoShot == true)
		if(mTimeAfterLastShoot >= mShootDelay)
		{
			Ogre::Vector3 xPosObject = mObjectNode->getPosition();
			Ogre::Vector2 xPos;
			xPos.x = xPosObject.x;
			xPos.y = xPosObject.y;
			mGameObjectsListener->addBullet(mObjectString, xPos, mDestinationDot);
			mTimeAfterLastShoot=0;
		}
		else
		{
			mTimeAfterLastShoot += evt.timeSinceLastFrame;
		}
}

Ogre::String GameObject::getObjectName()
{
	return mObjectName; 
}

void GameObject::setObjectString(Ogre::String xString)
{
	mObjectString = xString;
}

Ogre::String GameObject::getObjectString()
{
	return mObjectString;
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
