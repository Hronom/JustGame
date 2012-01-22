#include "Enemy.h"

Enemy::Enemy(iCore *xCore, std::string xEnemyName, Ogre::Vector2 xPos)
{
	mCore = xCore;

	mMoveDirection = Ogre::Vector3::ZERO;
	mMoveSpeed = 35.0f;

	mLookAt = Ogre::Vector2::ZERO;

	Ogre::ManualObject *xManualObject = new Ogre::ManualObject(xEnemyName+"_Manual");
	xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->position(Ogre::Vector3(0,5,0));
	xManualObject->position(Ogre::Vector3(13,0,0));
	xManualObject->position(Ogre::Vector3(0,-5,0));
	xManualObject->end();

	xManualObject->convertToMesh(xEnemyName+"_Mesh");

	Ogre::Entity* xPlayerEntity = mCore->getSceneManager()->createEntity(xEnemyName+"_Entity", xEnemyName+"_Mesh");

	mObjectNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mObjectNode->attachObject(xPlayerEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));
}

Enemy::~Enemy()
{
}

void Enemy::update(const Ogre::FrameEvent& evt)
{
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mObjectNode->getPosition();
	
	Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);
}

std::string Enemy::getName()
{
	return "lol"; 
}

Ogre::Vector3 Enemy::getCurrentPos()
{
	return mObjectNode->getPosition();
}

void Enemy::acceptCurrentPos()
{
}

void Enemy::rejectCurrentPos()
{
}

Ogre::Quaternion Enemy::getCurrentOrientation()
{
	return mObjectNode->getOrientation();
}

void Enemy::moveUp(bool doMove)
{
	if(doMove == true)
		mMoveDirection += Ogre::Vector3(1,0,0);
	else 
		mMoveDirection -= Ogre::Vector3(1,0,0);
}

void Enemy::moveDown(bool doMove)
{
	if(doMove == true)
		mMoveDirection -= Ogre::Vector3(1,0,0);
	else 
		mMoveDirection += Ogre::Vector3(1,0,0);
}

void Enemy::moveRight(bool doMove)
{
	if(doMove == true)
		mMoveDirection -= Ogre::Vector3(0,1,0);
	else 
		mMoveDirection += Ogre::Vector3(0,1,0);
}

void Enemy::moveLeft(bool doMove)
{
	if(doMove == true)
		mMoveDirection += Ogre::Vector3(0,1,0);
	else 
		mMoveDirection -= Ogre::Vector3(0,1,0);
}

void Enemy::rotateTo(Ogre::Vector2 xDot)
{
	mLookAt = xDot;
}

void Enemy::shoot(bool doShoot)
{
	Ogre::Vector3 xPosObject = mObjectNode->getPosition();
	Ogre::Vector2 xPos;
	xPos.x = xPosObject.x;
	xPos.y = xPosObject.y;
	mCore->addBullet(xPos, mLookAt);
}
