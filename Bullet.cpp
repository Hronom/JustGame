#include "Bullet.h"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

Bullet::Bullet(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectType, Ogre::Vector2 xPos, Ogre::Vector2 xDestination): GameObject(xCore, xGameObjectsListener, xObjectName, xObjectType)
{
	mHealthCount = 1;
	mDamage = 10;
	mMoveSpeed = 5.0f;

	mCanDoShot = false;
	mShootDelay = 0;
	mTimeAfterLastShoot = mShootDelay;

	GameObject::mDestinationDot = xDestination;
	GameObject::mMoveDirection = Ogre::Vector3(1,0,0);


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


	// create Entity
	mEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");
	// connect Entity to Node
	mObjectNode->attachObject(mEntity);

	// create Physical Body
	// starting xPosition of the box
	Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);

	// after that create the Bullet shape with the calculated xSize
	mSphereShape = new OgreBulletCollisions::SphereCollisionShape(mObjectRadius);
	// and the Bullet rigid body
	if(mObjectType == 2)
		mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld(), BULLET_GROUP, ENEMY_GROUP | BULLET_GROUP);
	else
		mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld(), BULLET_GROUP, PLAYER_GROUP | BULLET_GROUP);

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

	mRigidBody->getBulletRigidBody()->setUserPointer(this);

	mLiveTime = 1.0f;
	mTimeBeforeDelete = 0.3f;

	// ROTATE Ogre SceneNode
	Ogre::Vector3 xDirection = Ogre::Vector3(GameObject::mDestinationDot.x, GameObject::mDestinationDot.y, 0) - GameObject::mObjectNode->getPosition();
	Ogre::Vector3 xSrc = GameObject::mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mObjectNode->rotate(xQuat);

	// APPLY ROTATE to Bullet RigidBody
	btTransform xRigidBodyTransform = mRigidBody->getBulletRigidBody()->getWorldTransform();
	xRigidBodyTransform.setRotation(OgreBulletCollisions::OgreBtConverter::to(mObjectNode->getOrientation()));
	mRigidBody->getBulletRigidBody()->setWorldTransform(xRigidBodyTransform);

	// MOVE
	Ogre::Vector3 xVector;
	xVector = mMoveDirection * mMoveSpeed;
	xVector =  mObjectNode->getOrientation() * xVector;

	mRigidBody->getBulletRigidBody()->applyCentralImpulse(OgreBulletCollisions::OgreBtConverter::to(xVector));
}

Bullet::~Bullet()
{
	mCore->getDynamicsWorld()->getBulletDynamicsWorld()->removeRigidBody(mRigidBody->getBulletRigidBody());
	delete mRigidBody->getBulletRigidBody()->getMotionState();
	delete mRigidBody->getBulletRigidBody();

	delete mSphereShape;

	mObjectNode->detachAllObjects();
	mCore->getSceneManager()->destroyManualObject(mManualObject);
	mCore->getSceneManager()->destroyEntity(mEntity);
}

void Bullet::update(const Ogre::FrameEvent& evt)
{
	if(mHealthCount > 0)
	{
		if(mLiveTime > 0)
		{
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

int Bullet::getDamage()
{
	mHealthCount = 0;
	int xDamage = mDamage;
	mDamage = 0;
	return xDamage;
}