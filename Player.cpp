#include "Player.h"

Player::Player(Ogre::SceneManager *xSceneManager, Ogre::Vector2 xPos)
{
	mMoveDirection = Ogre::Vector3::ZERO;
	mMoveSpeed = 35.0f;

	mLookAt = Ogre::Vector2::ZERO;

	Ogre::ManualObject *xManualObject = new Ogre::ManualObject("Manual");
	xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->position(Ogre::Vector3(0,5,0));
	xManualObject->position(Ogre::Vector3(13,0,0));
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->end();

	xManualObject->convertToMesh("PlayerMesh");

	Ogre::Entity* xPlayerEntity = xSceneManager->createEntity("PlayerEntity", "PlayerMesh");

	mPlayerNode = xSceneManager->getRootSceneNode()->createChildSceneNode();
	mPlayerNode->attachObject(xPlayerEntity);	
	mPlayerNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));
}

Player::~Player()
{
}

void Player::update(const Ogre::FrameEvent& evt)
{
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mPlayerNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mPlayerNode->getPosition();
	
	Ogre::Vector3 xSrc = mPlayerNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mPlayerNode->rotate(xQuat);

	/*Ogre::Vector3 xSrc = mPlayerNode->getOrientation() * Ogre::Vector3::UNIT_X;
	if ((1.0f + xSrc.dotProduct(xDirection)) < 0.0001f) 
	{
		mPlayerNode->yaw(Ogre::Degree(180));
	}
	else
	{
		Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
		mPlayerNode->rotate(xQuat);
	}*/
}

std::string Player::getName()
{
	return "lol"; 
}

Ogre::Vector3 Player::getCurrentPos()
{
	return mPlayerNode->getPosition();
}

void Player::acceptCurrentPos()
{
}

void Player::rejectCurrentPos()
{
}

Ogre::Quaternion Player::getCurrentOrientation()
{
	return mPlayerNode->getOrientation();
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

void Player::shoot()
{
}
