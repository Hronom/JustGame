#include "Player.h"

Player::Player(iCore *xCore, Ogre::String xObjectName, Ogre::Vector2 xPos): GameObject(xCore, xObjectName)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	isCanShoot = false;
	mTimeAfterLastShoot = mShootDelay;

	mLookAt = Ogre::Vector2(1.0f,1.0f);


	Ogre::ManualObject *xManualObject = mCore->getSceneManager()->createManualObject(mObjectName+"_Manual");
 
    float const radius = 7;
 
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
}

Player::~Player()
{
}
