#include "Enemy.h"

#include "iGameObjectsListener.h"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

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
	//mObjectEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", "cube.mesh");
	//mObjectEntity->setMaterialName("Examples/BumpyMetal");

	// create Physical Body
	// starting xPosition of the box
	Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);

	// we need the bounding box of the box to be able to set the xSize of the Bullet-box
	Ogre::AxisAlignedBox xBoundingBox = mObjectEntity->getBoundingBox();

	Ogre::Vector3 xSize = Ogre::Vector3::ZERO;	// xSize of the box
	xSize = xBoundingBox.getSize(); 
	xSize.z = 7.0f;
	xSize /= 2.0f; // only the half needed
	xSize *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller xSize
	// (Bullet 2.76 Physics SDK Manual page 18)

	mObjectNode->attachObject(mObjectEntity);
	//mObjectNode->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us
	//xSize *= 0.051f;						// don't forget to scale down the Bullet-box too

	// after that create the Bullet shape with the calculated xSize
	mBoxShape = new OgreBulletCollisions::BoxCollisionShape(xSize);
	// and the Bullet rigid body
	mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld());
	mRigidBody->setShape(mObjectNode,
		mBoxShape,
		0.6f,			// dynamic body restitution
		0.6f,			// dynamic body friction
		0.1f, 			// dynamic bodymass
		xPosition,		// starting xPosition of the box
		Ogre::Quaternion(0,0,0,1));// orientation of the box
	
	mRigidBody->getBulletRigidBody()->setLinearFactor(btVector3(1,1,0));
	mRigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 1));
	mRigidBody->setCastShadows(false);

	/*mObjectNode->attachObject(mObjectEntity);	
	mObjectNode->setPosition(Ogre::Vector3(xPos.x, xPos.y, 0));*/

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
		// MOVE Ogre SceneNode
		Ogre::Real xMove = mMoveSpeed * evt.timeSinceLastFrame;
		mObjectNode->translate(mMoveDirection * xMove, Ogre::Node::TS_LOCAL);

		// ROTATE Ogre SceneNode
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

		// APPLY to Bullet RigidBody
		btTransform xRigidBodyTransform = mRigidBody->getBulletRigidBody()->getWorldTransform();
		xRigidBodyTransform.setOrigin(OgreBulletCollisions::OgreBtConverter::to(mObjectNode->getPosition()));
		xRigidBodyTransform.setRotation(OgreBulletCollisions::OgreBtConverter::to(mObjectNode->getOrientation()));
		mRigidBody->getBulletRigidBody()->setWorldTransform(xRigidBodyTransform);
		
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
