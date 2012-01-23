#include "Player.h"

Player::Player(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	mCanDoShot = false;
	mTimeAfterLastShoot = mShootDelay;

	mDestinationDot = Ogre::Vector2(1.0f,1.0f);



	mObjectRadius = 5;
	
	mManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    float const xAccuracy = 35;
    mManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    unsigned xPoint_index = 0;
    for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy) 
	{
        mManualObject->position(mObjectRadius * cos(xTheta), mObjectRadius * sin(xTheta), 0);
        mManualObject->index(xPoint_index++);
    }
    mManualObject->index(0); // Rejoins the last point to the first.
    mManualObject->end();
    mManualObject->convertToMesh(mObjectName+"_Mesh");



	mObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");

	mObjectNode->attachObject(mObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));
}

Player::~Player()
{
	 mObjectNode->detachAllObjects();
	 mCore->getSceneManager()->destroyManualObject(mManualObject);
	 mCore->getSceneManager()->destroyEntity(mObjectEntity);
}
