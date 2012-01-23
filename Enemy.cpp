#include "Enemy.h"

#include "iGameObjectsListener.h"

Enemy::Enemy(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	mCanDoShot = false;
	mTimeAfterLastShoot = mShootDelay;

	mDestinationDot = Ogre::Vector2(1.0f,1.0f);


	
	mObjectRadius = 7;
	
	Ogre::ManualObject *xManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    float const xAccuracy = 35;
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    unsigned xPoint_index = 0;
    for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy) 
	{
        xManualObject->position(mObjectRadius * cos(xTheta), mObjectRadius * sin(xTheta), 0);
        xManualObject->index(xPoint_index++);
    }
    xManualObject->index(0); // Rejoins the last point to the first.
    xManualObject->end();
    xManualObject->convertToMesh(mObjectName+"_Mesh");



	Ogre::Entity* xObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");

	mObjectNode->attachObject(xObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));

	mTimeBeforeDelete = 0.3f;
}

Enemy::~Enemy()
{
}

void Enemy::update(const Ogre::FrameEvent& evt)
{
	if(mHealthCount > 0)
	{
		// MOVE
		Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
		mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);



		// ROTATE
		Ogre::Vector3 xDirection = Ogre::Vector3(mDestinationDot.x, mDestinationDot.y, 0) - mObjectNode->getPosition();
		xDirection.z = 0;

		Ogre::Vector3 xSrc = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
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



		// SHOOT!!!
		if(mCanDoShot == true)
			if(mTimeAfterLastShoot >= mShootDelay)
			{
				Ogre::Vector3 xPosObject = mObjectNode->getPosition();
				Ogre::Vector2 xPos;
				xPos.x = xPosObject.x;
				xPos.y = xPosObject.y;
				mGameObjectsListener->addBullet(mObjectString, xPos, mDestinationDot);
				mTimeAfterLastShoot=0;
			}
			else
			{
				mTimeAfterLastShoot += evt.timeSinceLastFrame;
			}
	}
	else
	{
		if(mTimeBeforeDelete <=0) 
			mNeedDelete = true;
		else 
			mTimeBeforeDelete -= evt.timeSinceLastFrame;
	}
}
