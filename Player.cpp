#include "Player.h"

Player::Player(iCore *xCore, Ogre::Vector2 xPos)
{
	mCore = xCore;

	mMoveDirection = Ogre::Vector3::ZERO;
	mMoveSpeed = 35.0f;

	mShootDelay = 0.3;
	isCanShoot = false;
	mTimeAfterLastShoot = mShootDelay;

	mLookAt = Ogre::Vector2::ZERO;

	Ogre::ManualObject *xManualObject = new Ogre::ManualObject("Manual");
	xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->position(Ogre::Vector3(0,5,0));
	xManualObject->position(Ogre::Vector3(13,0,0));
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->end();

	xManualObject->convertToMesh("PlayerMesh");

	Ogre::Entity* xPlayerEntity = mCore->getSceneManager()->createEntity("PlayerEntity", "PlayerMesh");

	mObjectNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mObjectNode->attachObject(xPlayerEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));
}

Player::~Player()
{
}

void Player::update(const Ogre::FrameEvent& evt)
{
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mObjectNode->getPosition();
	
	Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);

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

std::string Player::getName()
{
	return "lol"; 
}

Ogre::Vector3 Player::getCurrentPos()
{
	return mObjectNode->getPosition();
}

void Player::acceptCurrentPos()
{
}

void Player::rejectCurrentPos()
{
}

Ogre::Quaternion Player::getCurrentOrientation()
{
	return mObjectNode->getOrientation();
}

void Player::moveUp(bool doMove)
{
	if(doMove == true)
		mMoveDirection += Ogre::Vector3(1,0,0);
	else 
		mMoveDirection -= Ogre::Vector3(1,0,0);
}

void Player::moveDown(bool doMove)
{
	if(doMove == true)
		mMoveDirection -= Ogre::Vector3(1,0,0);
	else 
		mMoveDirection += Ogre::Vector3(1,0,0);
}

void Player::moveRight(bool doMove)
{
	if(doMove == true)
		mMoveDirection -= Ogre::Vector3(0,1,0);
	else 
		mMoveDirection += Ogre::Vector3(0,1,0);
}

void Player::moveLeft(bool doMove)
{
	if(doMove == true)
		mMoveDirection += Ogre::Vector3(0,1,0);
	else 
		mMoveDirection -= Ogre::Vector3(0,1,0);
}

void Player::rotateTo(Ogre::Vector2 xDot)
{
	mLookAt = xDot;
}

void Player::shoot(bool doShoot)
{
	isCanShoot = doShoot;
}
