#include "Player.h"

Player::Player(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	isCanShoot = false;
	mTimeAfterLastShoot = mShootDelay;

	mDestinationDot = Ogre::Vector2(1.0f,1.0f);



	Ogre::ManualObject *xManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
	float const xRadius = 5;
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    float const xAccuracy = 35;
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    unsigned xPoint_index = 0;
    for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy) 
	{
        xManualObject->position(xRadius * cos(xTheta), xRadius * sin(xTheta), 0);
        xManualObject->index(xPoint_index++);
    }
    xManualObject->index(0); // Rejoins the last point to the first.
	/*xManualObject->position(Ogre::Vector3(0,-xRadius-1,0));
	xManualObject->position(Ogre::Vector3(0,xRadius-1,0));
	xManualObject->position(Ogre::Vector3(xRadius-1,0,0));
	xManualObject->position(Ogre::Vector3(0,-xRadius-1,0));*/
    xManualObject->end();
    xManualObject->convertToMesh(mObjectName+"_Mesh");



	Ogre::Entity* xObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");

	mObjectNode->attachObject(xObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));
}

Player::~Player()
{
}
