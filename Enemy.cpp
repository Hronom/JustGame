#include "Enemy.h"

#include "iGameObjectsListener.h"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

Enemy::Enemy(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos): GameObject(xCore, xGameObjectsListener, xObjectName)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	mCanDoShot = false;
	mTimeAfterLastShoot = mShootDelay;
	mDestinationDot = Ogre::Vector2(1.0f,1.0f);
	mTimeBeforeDelete = 0.7f;

	// create ManualObject
	mObjectRadius = 7;

	Ogre::ColourValue xColor = Ogre::ColourValue(0.0, 0.0, 1.0, 0.0);
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

	// create ObjectEntity
	mObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");

	// create Physical Body
	// starting xPosition of the box
	Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);

	mObjectNode->attachObject(mObjectEntity);

	// after that create the Bullet shape with the calculated xSize
	mSphereShape = new OgreBulletCollisions::SphereCollisionShape(mObjectRadius);
	// and the Bullet rigid body
	mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld());
	mRigidBody->setShape(mObjectNode,
		mSphereShape,
		0.0f,			// dynamic body restitution
		0.5f,			// dynamic body friction
		0.1f, 			// dynamic bodymass
		xPosition,		// starting xPosition of the box
		Ogre::Quaternion(0,0,0,1));// orientation of the box
	
	mRigidBody->getBulletRigidBody()->setLinearFactor(btVector3(1,1,0));
	mRigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 1));
	mRigidBody->setCastShadows(false);
}

Enemy::~Enemy()
{
	mObjectNode->detachAllObjects();
	mCore->getSceneManager()->destroyManualObject(mManualObject);
	mCore->getSceneManager()->destroyEntity(mObjectEntity);
}

void Enemy::update(const Ogre::FrameEvent& evt)
{
	if(mHealthCount > 0)
	{
		// ROTATE Ogre SceneNode
		Ogre::Vector3 xDirection = Ogre::Vector3(mDestinationDot.x, mDestinationDot.y, 0) - mObjectNode->getPosition();
		xDirection.z = 0;

		Ogre::Vector3 xSrcDirection = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
		xSrcDirection.z = 0;
		//xSrc.normalise();

		Ogre::Quaternion xQuat;		
		if ((1.0f + xSrcDirection.dotProduct(xDirection)) < 0.0001f)
			xQuat = Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z);
		else
			xQuat = xSrcDirection.getRotationTo(xDirection);

		mObjectNode->rotate(xQuat);

		// APPLY ROTATE to Bullet RigidBody
		btTransform xRigidBodyTransform = mRigidBody->getBulletRigidBody()->getWorldTransform();
		xRigidBodyTransform.setRotation(OgreBulletCollisions::OgreBtConverter::to(mObjectNode->getOrientation()));
		mRigidBody->getBulletRigidBody()->setWorldTransform(xRigidBodyTransform);

		// MOVE Ogre SceneNode
		Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
		Ogre::Vector3 xVector;
		xVector = mMoveDirection * xMove;
		xVector =  mObjectNode->getOrientation() * xVector;

		mRigidBody->getBulletRigidBody()->applyCentralForce(OgreBulletCollisions::OgreBtConverter::to(xVector));

		mRigidBody->enableActiveState();


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