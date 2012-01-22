#include "Bullet.h"

Bullet::Bullet(iCore *xCore, std::string xBulletName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mCore = xCore;

	mMoveDirection = Ogre::Vector3::ZERO;
	mMoveSpeed = 35.0f;

	mLookAt = xDestination;

	Ogre::ManualObject *xManualObject = new Ogre::ManualObject(xBulletName+"_Manual");
	xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	xManualObject->position(Ogre::Vector3(0,-0.3,0));
	xManualObject->position(Ogre::Vector3(0,0.3,0));
	xManualObject->position(Ogre::Vector3(7,0.3,0));
	xManualObject->position(Ogre::Vector3(7,-0.3,0));
	xManualObject->position(Ogre::Vector3(0,-0.3,0));
	xManualObject->end();

	xManualObject->convertToMesh(xBulletName+"_Mesh");

	Ogre::Entity* xEntity = mCore->getSceneManager()->createEntity(xBulletName+"_Entity", xBulletName+"_Mesh");

	mObjectNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode(xBulletName+"_Node");
	mObjectNode->attachObject(xEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));

	mMoveDirection += Ogre::Vector3(1,0,0);
	
	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mObjectNode->getPosition();
	Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);
}

Bullet::~Bullet()
{
}

void Bullet::update(const Ogre::FrameEvent& evt)
{
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

	Ogre::Vector3 xDirection = Ogre::Vector3(mLookAt.x, mLookAt.y, 0) - mObjectNode->getPosition();
}

std::string Bullet::getName()
{
	return "lol"; 
}

Ogre::Vector3 Bullet::getCurrentPos()
{
	return mObjectNode->getPosition();
}

void Bullet::acceptCurrentPos()
{
}

void Bullet::rejectCurrentPos()
{
}

Ogre::Quaternion Bullet::getCurrentOrientation()
{
	return mObjectNode->getOrientation();
}

void Bullet::moveUp(bool doMove)
{
}

void Bullet::moveDown(bool doMove)
{

}

void Bullet::moveRight(bool doMove)
{

}

void Bullet::moveLeft(bool doMove)
{

}

void Bullet::rotateTo(Ogre::Vector2 xDot)
{

}

void Bullet::shoot(bool doShoot)
{
}