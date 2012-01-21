#include "Player.h"

Player::Player(Ogre::SceneManager *xSceneManager, Ogre::Vector3 xPos)
{
	Ogre::ManualObject *xManualObject = new Ogre::ManualObject("Manual");
	xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	xManualObject->position(Ogre::Vector3(0,10,0));
	xManualObject->position(Ogre::Vector3(10,0,0));
	xManualObject->position(Ogre::Vector3(0,0,0));
	xManualObject->position(Ogre::Vector3(0,10,0));
	xManualObject->end();

	xManualObject->convertToMesh("PlayerMesh");

	Ogre::Entity* xPlayerEntity = xSceneManager->createEntity("PlayerEntity", "PlayerMesh");

	mPlayerNode = xSceneManager->getRootSceneNode()->createChildSceneNode();
	mPlayerNode->attachObject(xPlayerEntity);	
	mPlayerNode->setPosition(xPos);






	mDirection = Ogre::Vector3::ZERO;
}

Player::~Player()
{
}

void Player::update(const Ogre::FrameEvent& evt)
{
	Ogre::Real mWalkSpeed = 35.0f;
	

	Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;

	mPlayerNode->translate(mDirection * move);
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

void Player::movePlayerUp()
{
	mDirection = Ogre::Vector3(1,0,0);
}

void Player::movePlayerDown()
{
}

void Player::movePlayerLeft()
{
}

void Player::movePlayerRight()
{
}

void Player::playerShoot()
{
}
