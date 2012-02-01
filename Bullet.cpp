#include "Bullet.h"

Bullet::Bullet(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 1;
	mDamage = -10;
	mMoveSpeed = 45.0f;

	mCanDoShot = false;
	mShootDelay = 0;
	mTimeAfterLastShoot = mShootDelay;



	mObjectRadius = 1;
	
	Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 0.0, 0.0, 0.0);
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
		mManualObject->colour(xColor);
        mManualObject->index(xPoint_index++);
    }
    mManualObject->index(0); // Rejoins the last point to the first.
    mManualObject->end();
    mManualObject->convertToMesh(mObjectName+"_Mesh");



	mObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");
	mObjectNode->attachObject(mObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));

	GameObject::mDestinationDot = xDestination;
	GameObject::mMoveDirection = Ogre::Vector3(1,0,0);

	// ROTATE
	Ogre::Vector3 xDirection = Ogre::Vector3(GameObject::mDestinationDot.x, GameObject::mDestinationDot.y, 0) - GameObject::mObjectNode->getPosition();
	Ogre::Vector3 xSrc = GameObject::mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);

	mLiveTime = 1.0f;
	mTimeBeforeDelete = 0.3f;
}

Bullet::~Bullet()
{
	mObjectNode->detachAllObjects();
	mCore->getSceneManager()->destroyManualObject(mManualObject);
	mCore->getSceneManager()->destroyEntity(mObjectEntity);
}

void Bullet::update(const Ogre::FrameEvent& evt)
{
	if(mHealthCount > 0)
	{
		if(mLiveTime > 0)
		{
			// MOVE
			Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
			mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

			mLiveTime -= evt.timeSinceLastFrame;
		}
		else
		{
			mNeedDelete = true;
			mHealthCount = 0;
		}
	}
	else
	{
		if(mTimeBeforeDelete <= 0) 
			mNeedDelete = true;
		else 
			mTimeBeforeDelete -= evt.timeSinceLastFrame;
	}
}