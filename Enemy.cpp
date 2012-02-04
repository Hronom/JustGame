#include "Enemy.h"

#include "iGameObjectsListener.h"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

Enemy::Enemy(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectType, Ogre::Vector2 xPos): GameObject(xCore, xGameObjectsListener, xObjectName, xObjectType)
{
	mHealthCount = 100;
	mMoveSpeed = 15.0f;
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
	mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld(), ENEMY_GROUP, PLAYER_GROUP | ENEMY_GROUP | BULLET_GROUP);
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
}

Enemy::~Enemy()
{
	mCore->getDynamicsWorld()->getBulletDynamicsWorld()->removeRigidBody(mRigidBody->getBulletRigidBody());
	delete mRigidBody->getBulletRigidBody()->getMotionState();
	delete mRigidBody->getBulletRigidBody();

	delete mSphereShape;

	mObjectNode->detachAllObjects();
	mCore->getSceneManager()->destroyManualObject(mManualObject);
	mCore->getSceneManager()->destroyEntity(mEntity);
}

void Enemy::update(const Ogre::FrameEvent& evt)
{
	if(mHealthCount > 0)
	{
		rotateEnemy(evt.timeSinceLastFrame);
		moveEnemy(evt.timeSinceLastFrame);
		enemyShoot(evt.timeSinceLastFrame);

		mRigidBody->enableActiveState();
	}
	else
	{
		if(mTimeBeforeDelete <=0) 
			mNeedDelete = true;
		else 
			mTimeBeforeDelete -= evt.timeSinceLastFrame;
	}
}


void Enemy::rotateEnemy(Ogre::Real xTimeSinceLastFrame)
{
	// ROTATE Ogre SceneNode
	Ogre::Vector3 xDirection = Ogre::Vector3(mDestinationDot.x, mDestinationDot.y, 0) - mObjectNode->getPosition();
	xDirection.z = 0;

	Ogre::Vector3 xSrcDirection = mObjectNode->getOrientation() * Ogre::Vector3::UNIT_X;
	xSrcDirection.z = 0;
	//xSrcDirection.normalise();

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
}

void Enemy::moveEnemy(Ogre::Real xTimeSinceLastFrame)
{
	// MOVE Ogre SceneNode
	Ogre::Real xMove = mMoveSpeed * xTimeSinceLastFrame;
	//Ogre::Real xMove = mMoveSpeed;
	Ogre::Vector3 xVector;
	xVector = mMoveDirection * xMove;
	xVector =  mObjectNode->getOrientation() * xVector;

	mRigidBody->getBulletRigidBody()->applyCentralImpulse(OgreBulletCollisions::OgreBtConverter::to(xVector));

	// mRigidBody is the spaceship's btRigidBody
    btVector3 xCurrentVelocity = mRigidBody->getBulletRigidBody()->getLinearVelocity();
    btScalar xCurrentSpeed = xCurrentVelocity.length();
    if(xCurrentSpeed > mMoveSpeed) 
	{
        xCurrentVelocity *= mMoveSpeed/xCurrentSpeed;
        mRigidBody->getBulletRigidBody()->setLinearVelocity(xCurrentVelocity);
    }
}

void Enemy::enemyShoot(Ogre::Real xTimeSinceLastFrame)
{
	// SHOOT!!!
	if(mCanDoShot == true)
		if(mTimeAfterLastShoot >= mShootDelay)
		{
			Ogre::Vector3 xPosObject = mObjectNode->getPosition();
			Ogre::Vector2 xPos;
			xPos.x = xPosObject.x;
			xPos.y = xPosObject.y;
			mGameObjectsListener->addBullet(PLAYER_GROUP, xPos, mDestinationDot);
			mTimeAfterLastShoot=0;
		}
		else
		{
			mTimeAfterLastShoot += xTimeSinceLastFrame;
		}
}