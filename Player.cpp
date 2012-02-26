#include "Player.h"
#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <Utils.h>
#include <btBulletDynamicsCommon.h>

#include "IGameObjectsListener.h"

Player::Player(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos): MyGameObject(xGameObjectsListener, xObjectName, xObjectCollideWith)
{
	mHealthCount = 100;
	mMoveSpeed = 35.0f;
	mShootDelay = 0.3f;
	mShoot = false;
	mTimeSinceLastShot = mShootDelay;

	mDestinationDot = Ogre::Vector2(1.0f,1.0f);

	// create ManualObject
	float xObjectRadius  = 5;

	Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 1.0, 1.0, 0.0);
	mManualObject = new Ogre::ManualObject(mObjectName+"_Manual");
	// accuracy is the count of points (and lines).
	// Higher values make the circle smoother, but may slowdown the performance.
	// The performance also is related to the count of circles.
	float const xAccuracy = 5;
	mManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	unsigned xPoint_index = 0;
	for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy) 
	{
		mManualObject->position(xObjectRadius * cos(xTheta), xObjectRadius * sin(xTheta), 0);
		mManualObject->colour(xColor);
		mManualObject->index(xPoint_index++);
	}
	mManualObject->index(0); // Rejoins the last point to the first.
	mManualObject->end();
	mManualObject->convertToMesh(mObjectName+"_Mesh");

	// create Entity
	mEntity = JGC::Graphic::GraphicSystem::instance()->getSceneManager()->createEntity(mObjectName+"_Entity", mObjectName+"_Mesh");
	// connect Entity to Node
	mSceneNode = JGC::Graphic::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(xObjectName+"_Node");
	mSceneNode->attachObject(mEntity);

	// create Physical Body
	// starting xPosition of the box
	Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);
	mSceneNode->setPosition(xPosition);

	// after that create the Bullet shape with the calculated xSize
	mCollisionShape = new btSphereShape(xObjectRadius);
	// and the Bullet rigid body
	mMyMotionState = new JGC::Physics::MyMotionState(
		btTransform(JGC::toBtQuaternion(Ogre::Quaternion(0,0,0,1)), JGC::toBtVector3(xPosition)), mSceneNode);
	mRigidBody = new btRigidBody(0.1f, mMyMotionState, mCollisionShape, btVector3(0,0,0));
	mRigidBody->setRestitution(0.0f);
	mRigidBody->setFriction(0.5f);
	mRigidBody->setLinearFactor(btVector3(1,1,0));
	mRigidBody->setAngularFactor(btVector3(0, 0, 1));

	mRigidBody->setUserPointer(this);

	JGC::Physics::PhysicsSystem::instance()->getDynamicsWorld()->addRigidBody(mRigidBody, PLAYER_GROUP, PLAYER_GROUP | ENEMY_GROUP | BULLET_GROUP);
	
	mSoundListener = JGC::Sound::SoundSystem::instance()->getSoundListener();
	mSoundListener->move(xPosition.x, xPosition.y, xPosition.z);
	mSoundSource = JGC::Sound::SoundSystem::instance()->createSoundSource(xPosition.x, xPosition.y, xPosition.z, "../Media/Sound/impulse.wav", false);
}

Player::~Player()
{
	JGC::Sound::SoundSystem::instance()->destroySoundSource(mSoundSource);
	JGC::Graphic::GraphicSystem::instance()->getSceneManager()->destroyManualObject(mManualObject);
}

void Player::update(const Ogre::FrameEvent& evt)
{
	rotatePlayer(evt.timeSinceLastFrame);
	movePlayer(evt.timeSinceLastFrame);
	playerShoot(evt.timeSinceLastFrame);

	mRigidBody->activate();

	// Установка нового положения камеры
	Ogre::Vector3 xPlayerPos;
	xPlayerPos = mSceneNode->getPosition();

	mSoundListener->move(xPlayerPos.x, xPlayerPos.y, xPlayerPos.z);

	Ogre::Vector3 xNewCameraPos;
	xNewCameraPos = JGC::Graphic::GraphicSystem::instance()->getCamera()->getPosition();
	xNewCameraPos.x = xPlayerPos.x;
	xNewCameraPos.y = xPlayerPos.y;

	JGC::Graphic::GraphicSystem::instance()->getCamera()->setPosition(xNewCameraPos);
}

void Player::rotatePlayer(Ogre::Real xTimeSinceLastFrame)
{
	// ROTATE Ogre SceneNode
	Ogre::Vector3 xDirection = Ogre::Vector3(mDestinationDot.x, mDestinationDot.y, 0) - mSceneNode->getPosition();
	xDirection.z = 0;

	Ogre::Vector3 xSrcDirection = mSceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
	xSrcDirection.z = 0;
	//xSrcDirection.normalise();

	Ogre::Quaternion xQuat;		
	if ((1.0f + xSrcDirection.dotProduct(xDirection)) < 0.0001f)
		xQuat = Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z);
	else
		xQuat = xSrcDirection.getRotationTo(xDirection);

	mSceneNode->rotate(xQuat);

	// APPLY ROTATE to Bullet RigidBody
	btTransform xRigidBodyTransform = mRigidBody->getWorldTransform();
	xRigidBodyTransform.setRotation(JGC::toBtQuaternion(mSceneNode->getOrientation()));
	mRigidBody->setWorldTransform(xRigidBodyTransform);
}

void Player::movePlayer(Ogre::Real xTimeSinceLastFrame)
{
	// MOVE Ogre SceneNode
	Ogre::Real xMove = mMoveSpeed * xTimeSinceLastFrame;
	//Ogre::Real xMove = mMoveSpeed;
	Ogre::Vector3 xVector;
	xVector = mMoveDirection * xMove;
	xVector =  mSceneNode->getOrientation() * xVector;

	mRigidBody->applyCentralImpulse(JGC::toBtVector3(xVector));

	// mRigidBody is the spaceship's btRigidBody
	btVector3 xCurrentVelocity = mRigidBody->getLinearVelocity();
	btScalar xCurrentSpeed = xCurrentVelocity.length();
	if(xCurrentSpeed > mMoveSpeed) 
	{
		xCurrentVelocity *= mMoveSpeed/xCurrentSpeed;
		mRigidBody->setLinearVelocity(xCurrentVelocity);
	}
}

void Player::playerShoot(Ogre::Real xTimeSinceLastFrame)
{
	// SHOOT!!!
	if(mShoot == true)
		if(mTimeSinceLastShot >= mShootDelay)
		{
			Ogre::Vector3 xPosObject = mSceneNode->getPosition();
			Ogre::Vector2 xPos;
			xPos.x = xPosObject.x;
			xPos.y = xPosObject.y;
			mGameObjectsListener->addBullet(ENEMY_GROUP, xPos, mDestinationDot);
			mSoundSource->move(xPosObject.x,xPosObject.y,xPosObject.z);
			mSoundSource->play();
			mTimeSinceLastShot=0;
		}
		else
		{
			mTimeSinceLastShot += xTimeSinceLastFrame;
		}
}
