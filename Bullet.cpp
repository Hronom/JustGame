#include "Bullet.h"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

Bullet::Bullet(ICore *xCore, IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos, Ogre::Vector2 xDestination): MyGameObject(xCore, xGameObjectsListener, xObjectName, xObjectCollideWith)
{
	mHealthCount = 1;
	mMakeDamage = 10;
	mMoveSpeed = 5.0f;

	mShoot = false;
	mShootDelay = 0;
	mTimeSinceLastShot = mShootDelay;

	MyGameObject::mDestinationDot = xDestination;
	MyGameObject::mMoveDirection = Ogre::Vector3(1,0,0);


	Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 0.0, 0.0, 0.0);
	mManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
	mManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	mManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));	
	mManualObject->colour(xColor);
	mManualObject->position(Ogre::Vector3(-1.5f,0.3f,0.0f));
	mManualObject->colour(xColor);
	mManualObject->position(Ogre::Vector3(1.5f,0.3f,0.0f));
	mManualObject->colour(xColor);
	mManualObject->position(Ogre::Vector3(1.5f,-0.3f,0.0f));
	mManualObject->colour(xColor);
	mManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));
	mManualObject->colour(xColor);
	mManualObject->end();
	mManualObject->convertToMesh(mObjectName+"_Mesh");

	// create Entity
	mEntity = mCore->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");
	// connect Entity to Node
	mSceneNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode(xObjectName+"_Node");
	mSceneNode->attachObject(mEntity);

	// create Physical Body
	Ogre::AxisAlignedBox xBoundingBox = mEntity->getBoundingBox();

	Ogre::Vector3 xSize = Ogre::Vector3::ZERO;	// xSize of the box
	xSize = xBoundingBox.getSize(); 
	xSize.z = 3.0f;
	xSize /= 2.0f; // only the half needed
	xSize *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller xSize
	// (Bullet 2.76 Physics SDK Manual page 18)
	// starting xPosition of the box
	Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);

	// after that create the Bullet shape with the calculated xSize
	mCollisionShape = new OgreBulletCollisions::BoxCollisionShape(xSize);
	// and the Bullet rigid body
	mRigidBody = new OgreBulletDynamics::RigidBody(mObjectName+"_RigidBody", mCore->getDynamicsWorld(), BULLET_GROUP, mObjectCollideWith | BULLET_GROUP);

	mRigidBody->setShape(mSceneNode,
		mCollisionShape,
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
	Ogre::Vector3 xDirection = Ogre::Vector3(MyGameObject::mDestinationDot.x, MyGameObject::mDestinationDot.y, 0) - MyGameObject::mSceneNode->getPosition();
	Ogre::Vector3 xSrc = MyGameObject::mSceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
	mSceneNode->rotate(xQuat);

	// APPLY ROTATE to Bullet RigidBody
	btTransform xRigidBodyTransform = mRigidBody->getBulletRigidBody()->getWorldTransform();
	xRigidBodyTransform.setRotation(OgreBulletCollisions::OgreBtConverter::to(mSceneNode->getOrientation()));
	mRigidBody->getBulletRigidBody()->setWorldTransform(xRigidBodyTransform);

	// MOVE
	Ogre::Vector3 xVector;
	xVector = mMoveDirection * mMoveSpeed;
	xVector =  mSceneNode->getOrientation() * xVector;

	mRigidBody->getBulletRigidBody()->applyCentralImpulse(OgreBulletCollisions::OgreBtConverter::to(xVector));
}

Bullet::~Bullet()
{
	mCore->getSceneManager()->destroyManualObject(mManualObject);
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
	int xDamage = mMakeDamage;
	mMakeDamage = 0;
	return xDamage;
}