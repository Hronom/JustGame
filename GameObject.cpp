#include "GameObject.h"

#include "iCore.h"

GameObject::GameObject(iCore *xCore, Ogre::String xObjectName)
{
	mCore = xCore;

	mObjectNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode(xObjectName+"_Node");

	mMoveDirection = Ogre::Vector3::ZERO;
	mMoveSpeed = 0;
	mLookAt = Ogre::Vector2::ZERO;

	mObjectName = xObjectName;
	mDamage = 0;
	mHealthCount = 0;
	mShootDelay = 0;
	isCanShoot = false;
	mTimeAfterLastShoot = mShootDelay;
}

GameObject::~GameObject()
{

}

void GameObject::update(const Ogre::FrameEvent& evt)
{
	// MOVE
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

	// ROTATE
	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mObjectNode->getPosition();
	//xDirection.x = 0;
	xDirection.z = 0;

	Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	//xSrc.x = 0;
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
	if(isCanShoot == true)
		if(mTimeAfterLastShoot >= mShootDelay)
		{
			Ogre::Vector3 xPosObject = mObjectNode->getPosition();
			Ogre::Vector2 xPos;
			xPos.x = xPosObject.x;
			xPos.y = xPosObject.y;
			mCore->addBullet(xPos, mLookAt);
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

Ogre::Vector2 GameObject::getCurrentPos()
{
	Ogre::Vector3 xVector3Pos;
	Ogre::Vector2 xVector2Pos;

	xVector3Pos = mObjectNode->getPosition();

	xVector2Pos.x = xVector3Pos.x;
	xVector2Pos.y = xVector3Pos.y;

	return xVector2Pos;
}

int GameObject::getDamage()
{
	return mDamage;
}

void GameObject::doDamage(int xDamage)
{
	mHealthCount -= xDamage;
}

int GameObject::getCurrentHealth()
{
	return mHealthCount;
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

void GameObject::rotateTo(Ogre::Vector2 xDot)
{
	mLookAt = xDot;
}

void GameObject::shoot(bool doShoot)
{
	isCanShoot = doShoot;
}
