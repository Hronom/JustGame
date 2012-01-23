#include "Bullet.h"

Bullet::Bullet(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 0;
	mDamage = 10;
	mMoveSpeed = 45.0f;

	isCanShoot = false;
	mShootDelay = 0;
	mTimeAfterLastShoot = mShootDelay;



	Ogre::ManualObject *xManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
	float const xRadius = 1;
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
    xManualObject->end();
    xManualObject->convertToMesh(mObjectName+"_Mesh");



	Ogre::Entity* xObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");
	mObjectNode->attachObject(xObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));

	GameObject::mDestinationDot = xDestination;
	GameObject::mMoveDirection = Ogre::Vector3(1,0,0);

	// ROTATE
	Ogre::Vector3 xDirection = Ogre::Vector3(GameObject::mDestinationDot.x, GameObject::mDestinationDot.y, 0) - GameObject::mObjectNode->getPosition();
	Ogre::Vector3 xSrc = GameObject::mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);
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