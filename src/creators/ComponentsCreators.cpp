#include "ComponentsCreators.h"

#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <Utils.h>

namespace JG
{
    GraphBody* cBackgroundGraphBody(QString xComponentName)
    {
        // create ManualObject
        Ogre::ManualObject *xManualObject;
        xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());

        Ogre::ColourValue xColor = Ogre::ColourValue(0.104f, 0.234f, 0.140f, 0.0f);
        Ogre::Real xGridDistance = 10.0f;
        for (Ogre::Real i = -50.0f; i < 50.0f; i+=1.0f)
        {
            // Draw vertical line
            xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
            xManualObject->position(i * xGridDistance, -500.0f, -100.0f);
            xManualObject->colour(xColor);
            xManualObject->position(i * xGridDistance, +500.0f, -100.0f);
            xManualObject->colour(xColor);
            xManualObject->end();
            // Draw gorizontal line
            xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
            xManualObject->position(-500.0f, i * xGridDistance, -100.0f);
            xManualObject->colour(xColor);
            xManualObject->position(+500.0f, i * xGridDistance, -100.0f);
            xManualObject->colour(xColor);
            xManualObject->end();
        }
        xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

        // create Entity
        Ogre::Entity *xEntity;
        xEntity = JGC::GraphicSystem::instance()->getSceneManager()->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());

        // create SceneNode
        Ogre::SceneNode *xSceneNode;
        xSceneNode = JGC::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
        // connect Entity to Node
        xSceneNode->attachObject(xEntity);

        // create component
        GraphBody* xGraphBody;
        xGraphBody = new GraphBody();

        xGraphBody->mManualObject = xManualObject;
        xGraphBody->mEntity = xEntity;
        xGraphBody->mSceneNode = xSceneNode;

        return xGraphBody;
    }

    GraphBody* cPlayerGraphBody(QString xComponentName)
    {
        Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 1.0, 1.0, 0.0);
        // create ManualObject
        Ogre::ManualObject *xManualObject;
        xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
        // accuracy is the count of points (and lines).
        // Higher values make the circle smoother, but may slowdown the performance.
        // The performance also is related to the count of circles.
        xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
        const float xObjectRadius  = 5;
        const float xAccuracy = 5;
        unsigned xPoint_index = 0;
        for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy)
        {
            xManualObject->position(xObjectRadius * cos(xTheta), xObjectRadius * sin(xTheta), 0);
            xManualObject->colour(xColor);
            xManualObject->index(xPoint_index++);
        }
        xManualObject->index(0); // Rejoins the last point to the first.
        xManualObject->end();
        xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

        // create Entity
        Ogre::Entity *xEntity;
        xEntity = JGC::GraphicSystem::instance()->getSceneManager()->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
        xEntity->setUserAny(Ogre::Any(new int(0)));
        // create SceneNode
        Ogre::SceneNode *xSceneNode;
        xSceneNode = JGC::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
        // connect Entity to Node
        xSceneNode->attachObject(xEntity);

        Ogre::Vector3 xPosition = Ogre::Vector3(0, 0, 0);
        xSceneNode->setPosition(xPosition);

        Ogre::Quaternion xOrientation = Ogre::Quaternion(0, 0, 0, 1);
        xSceneNode->setOrientation(xOrientation);

        // create component
        GraphBody* xGraphBody;
        xGraphBody = new GraphBody();

        xGraphBody->mManualObject = xManualObject;
        xGraphBody->mEntity = xEntity;
        xGraphBody->mSceneNode = xSceneNode;

        return xGraphBody;
    }

    GraphBody* cEnemyGraphBody(QString xComponentName)
    {
        Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 1.0, 1.0, 0.0);
        // create ManualObject
        Ogre::ManualObject *xManualObject;
        xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
        // accuracy is the count of points (and lines).
        // Higher values make the circle smoother, but may slowdown the performance.
        // The performance also is related to the count of circles.
        xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
        const float xObjectRadius  = 7;
        const float xAccuracy = 35;
        unsigned xPoint_index = 0;
        for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy)
        {
            xManualObject->position(xObjectRadius * cos(xTheta), xObjectRadius * sin(xTheta), 0);
            xManualObject->colour(xColor);
            xManualObject->index(xPoint_index++);
        }
        xManualObject->index(0); // Rejoins the last point to the first.
        xManualObject->end();
        xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

        // create Entity
        Ogre::Entity *xEntity;
        xEntity = JGC::GraphicSystem::instance()->getSceneManager()->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
        xEntity->setUserAny(Ogre::Any(new int(0)));
        // create SceneNode
        Ogre::SceneNode *xSceneNode;
        xSceneNode = JGC::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
        // connect Entity to Node
        xSceneNode->attachObject(xEntity);

        //Ogre::Vector3 xPosition = Ogre::Vector3(xPos.x, xPos.y, 0);
        //mSceneNode->setPosition(xPosition);

        // create component
        GraphBody* xGraphBody;
        xGraphBody = new GraphBody();

        xGraphBody->mManualObject = xManualObject;
        xGraphBody->mEntity = xEntity;
        xGraphBody->mSceneNode = xSceneNode;

        return xGraphBody;
    }

    GraphBody* cBulletGraphBody(QString xComponentSuffix, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination)
    {
        QString xComponentName;
        xComponentName = xComponentSuffix;
        xComponentName += QString::number(mBulletsCount);
        mBulletsCount++;

        Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 0.0, 0.0, 0.0);
        Ogre::ManualObject *xManualObject;
        xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
        xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
        xManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));
        xManualObject->colour(xColor);
        xManualObject->position(Ogre::Vector3(-1.5f,0.3f,0.0f));
        xManualObject->colour(xColor);
        xManualObject->position(Ogre::Vector3(1.5f,0.3f,0.0f));
        xManualObject->colour(xColor);
        xManualObject->position(Ogre::Vector3(1.5f,-0.3f,0.0f));
        xManualObject->colour(xColor);
        xManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));
        xManualObject->colour(xColor);
        xManualObject->end();
        xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

        // create Entity
        Ogre::Entity *xEntity;
        xEntity = JGC::GraphicSystem::instance()->getSceneManager()->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
        xEntity->setUserAny(Ogre::Any(new int(0)));
        // create SceneNode
        Ogre::SceneNode *xSceneNode;
        xSceneNode = JGC::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
        // connect Entity to Node
        xSceneNode->attachObject(xEntity);

        // Set position of SceneNode
        xSceneNode->setPosition(xPosition);

        // Rotate SceneNode
        Ogre::Vector3 xDirection = xDestination - xPosition;
        Ogre::Vector3 xSrc = xSceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
        Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
        xSceneNode->rotate(xQuat);

        // create component
        GraphBody* xGraphBody;
        xGraphBody = new GraphBody();

        xGraphBody->mManualObject = xManualObject;
        xGraphBody->mEntity = xEntity;
        xGraphBody->mSceneNode = xSceneNode;

        return xGraphBody;
    }

    void dBulletGraphBody(GraphBody* xGraphBody)
    {
        mBulletsCount--;
        dGraphBody(xGraphBody);
    }

    void dGraphBody(GraphBody* xGraphBody)
    {
        JGC::GraphicSystem::instance()->getSceneManager()->destroyManualObject(xGraphBody->mManualObject);
        JGC::GraphicSystem::instance()->getSceneManager()->destroyEntity(xGraphBody->mEntity);
        xGraphBody->mSceneNode->removeAndDestroyAllChildren();
        JGC::GraphicSystem::instance()->getSceneManager()->destroySceneNode(xGraphBody->mSceneNode);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PhysBody* cPlayerPhysBody()
    {
        // after that create the Bullet shape with the calculated xSize
        btVector3 xSize;

        btCollisionShape *xCollisionShape;
        xCollisionShape = new btBoxShape(xSize);
        // and the Bullet rigid body
        btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)));
        btRigidBody *xRigidBody;
        xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0, 0, 0));
        xRigidBody->setRestitution(0.0f);
        xRigidBody->setFriction(0.5f);
        xRigidBody->setLinearFactor(btVector3(1, 1, 0));
        xRigidBody->setAngularFactor(btVector3(0, 0, 1));

        JGC::PhysicsSystem::instance()->getDynamicsWorld()->addRigidBody(xRigidBody, PLAYER_GROUP, PLAYER_GROUP | ENEMY_GROUP | BULLET_GROUP);

        // create component
        PhysBody* xPhysBody;
        xPhysBody = new PhysBody();

        xRigidBody->setUserPointer(xPhysBody);

        xPhysBody->mCollisionShape = xCollisionShape;
        xPhysBody->mRigidBody = xRigidBody;

        return xPhysBody;
    }

    PhysBody* cEnemyPhysBody()
    {
        // after that create the Bullet shape with the calculated xSize
        btVector3 xSize;

        btCollisionShape *xCollisionShape;
        xCollisionShape = new btBoxShape(xSize);
        // and the Bullet rigid body
        btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0)));
        btRigidBody *xRigidBody;
        xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0,0,0));
        xRigidBody->setRestitution(0.0f);
        xRigidBody->setFriction(0.5f);
        xRigidBody->setLinearFactor(btVector3(1,1,0));
        xRigidBody->setAngularFactor(btVector3(0, 0, 1));

        JGC::PhysicsSystem::instance()->getDynamicsWorld()->addRigidBody(xRigidBody, ENEMY_GROUP, PLAYER_GROUP | ENEMY_GROUP | BULLET_GROUP);

        // create component
        PhysBody* xPhysBody;
        xPhysBody = new PhysBody();

        xRigidBody->setUserPointer(xPhysBody);

        xPhysBody->mCollisionShape = xCollisionShape;
        xPhysBody->mRigidBody = xRigidBody;

        return xPhysBody;
    }

    PhysBody* cBulletPhysBody(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation)
    {
        // after that create the Bullet shape with the calculated xSize
        btVector3 xSize;

        btCollisionShape *xCollisionShape;
        xCollisionShape = new btBoxShape(xSize);
        // and the Bullet rigid body
        btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(xOrientation, xPosition));
        btRigidBody *xRigidBody;
        xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0,0,0));
        xRigidBody->setRestitution(0.0f);
        xRigidBody->setFriction(0.5f);
        xRigidBody->setLinearFactor(btVector3(1,1,0));
        xRigidBody->setAngularFactor(btVector3(0, 0, 1));

        JGC::PhysicsSystem::instance()->getDynamicsWorld()->addRigidBody(xRigidBody, BULLET_GROUP, xObjectCollideWith | BULLET_GROUP);

        // MOVE
        Ogre::Vector3 xVector;
        float xMoveSpeed = 5.0f;
        xVector = Ogre::Vector3(1,0,0) * xMoveSpeed;
        xVector =  JGC::Utils::toOgreQuaternion(xOrientation) * xVector;
        xRigidBody->applyCentralImpulse(JGC::Utils::toBtVector3(xVector));

        // create component
        PhysBody* xPhysBody;
        xPhysBody = new PhysBody();

        xRigidBody->setUserPointer(xPhysBody);

        xPhysBody->mCollisionShape = xCollisionShape;
        xPhysBody->mRigidBody = xRigidBody;

        return xPhysBody;
    }

    void dPhysBody(PhysBody* xPhysBody)
    {
        JGC::PhysicsSystem::instance()->getDynamicsWorld()->removeRigidBody(xPhysBody->mRigidBody);
        delete xPhysBody->mRigidBody->getMotionState();
        delete xPhysBody->mRigidBody;
        delete xPhysBody->mCollisionShape;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CameraTrackable* cCameraTrackable(QString xCameraName)
    {
        Ogre::Camera* xCamera;
        xCamera = JGC::GraphicSystem::instance()->getCamera();

        // create component
        CameraTrackable* xCameraTrackable;
        xCameraTrackable = new CameraTrackable();

        xCameraTrackable->mCamera = xCamera;

        return xCameraTrackable;
    }

    void dCameraTrackable()
    {

    }

    Health* cHealth(qint32 xHealthCurrent, qint32 xHealthTotal)
    {
        // create component
        Health* xHealth;
        xHealth = new Health();

        xHealth->mHealthTotal = xHealthTotal;
        xHealth->mHealthCurrent = xHealthCurrent;

        return xHealth;
    }

    DoDamage* cDoDamage(qint32 xDamageCount)
    {
        // create component
        DoDamage* xDoDamage;
        xDoDamage = new DoDamage();

        xDoDamage->mDamageCount = xDamageCount;

        return xDoDamage;
    }

    PlayerControllable* cPlayerControllable()
    {
        // create component
        PlayerControllable* xPlayerControllable;
        xPlayerControllable = new PlayerControllable();

        return xPlayerControllable;
    }

    Weapon *cWeapon(float xShootDelay)
    {
        // create component
        Weapon* xWeapon;
        xWeapon = new Weapon();
        xWeapon->mShootDelay = xShootDelay;
        xWeapon->mTimeSinceLastShot = xShootDelay;

        return xWeapon;
    }

     Bullet* cBullet(float xTotalLiveTime)
     {
         // create component
         Bullet* xBullet;
         xBullet = new Bullet();
         xBullet->mTotalLiveTime = xTotalLiveTime;
         xBullet->mLiveTime = 0;

         return xBullet;
     }

     void dBullet(Bullet *xBullet)
     {
         delete xBullet;
     }
}

