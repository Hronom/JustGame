#include "Bullet.h"

Bullet::Bullet(iCore *xCore, Ogre::String xObjectName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination): GameObject(xCore, xObjectName)
{
	mDamage = 10;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	isCanShoot = false;
	mTimeAfterLastShoot = mShootDelay;

	mMoveDirection = Ogre::Vector3(1,0,0);

	Ogre::ManualObject *xManualObject = mCore->getSceneManager()->createManualObject(mObjectName+"_Manual");
 
    float const radius = 3;
 
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    float const accuracy = 35;
 
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
 
    unsigned point_index = 0;
    for(float theta = 0; theta <= 2 * Ogre::Math::PI; theta += Ogre::Math::PI / accuracy) 
	{
        xManualObject->position(radius * cos(theta), radius * sin(theta), 0);
        xManualObject->index(point_index++);
    }

    xManualObject->index(0); // Rejoins the last point to the first.
 
    xManualObject->end();
 
    xManualObject->convertToMesh(mObjectName+"_Mesh");

	Ogre::Entity* xObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");

	mObjectNode->attachObject(xObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));




	this->rotateTo(xDestination);

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

}

Bullet::~Bullet()
{
}

void Bullet::update(const Ogre::FrameEvent& evt)
{
	// MOVE
	Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
	mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);
}