#include "AIControlSys.h"

#include <InputSystem.h>
#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <IComponent.h>
#include <Utils.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

AIControlSys::AIControlSys()
{
    JGC::CountersSystem::instance()->addCounter("BulletsCount");
}

AIControlSys::~AIControlSys()
{
    JGC::CountersSystem::instance()->removeCounter("BulletsCount");
}

void AIControlSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    btVector3 xPlayerPos;
    xPlayerPos.setZero();

    // Get player pos
    {
        QVector<JGC::Entity*> xPlayersEntitys;
        xPlayersEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerControlNode);

        if(xPlayersEntitys.size()>0)
        {
            PhysBodyCom *xPlayerPhysBody;
            xPlayerPhysBody = xPlayersEntitys.at(0)->getComponent<PhysBodyCom>();

            xPlayerPos.setX(xPlayerPhysBody->mRigidBody->getWorldTransform().getOrigin().x());
            xPlayerPos.setY(xPlayerPhysBody->mRigidBody->getWorldTransform().getOrigin().y());
            xPlayerPos.setZ(0);
        }
    }



    QVector<JGC::Entity*> xEnemysEntitys;
    xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::AIControlNode);

    for(int i = 0; i < xEnemysEntitys.size(); ++i)
    {
        HealthCom *xHealthCom;
        xHealthCom = xEnemysEntitys.at(i)->getComponent<HealthCom>();

        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = xEnemysEntitys.at(i)->getComponent<GraphBodyCom>();

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBodyCom->mSceneNode;

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEnemysEntitys.at(i)->getComponent<PhysBodyCom>();

        btRigidBody *xRigidBody;
        xRigidBody = xPhysBodyCom->mRigidBody;

        // Rotate
        {
            // ROTATE Ogre SceneNode
            Ogre::Vector3 xDirection = JGC::Utils::toOgreVector3(xPlayerPos) - xSceneNode->getPosition();
            xDirection.z = 0;

            Ogre::Vector3 xSrcDirection = xSceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
            xSrcDirection.z = 0;
            //xSrcDirection.normalise();

            Ogre::Quaternion xQuat;
            if((1.0f + xSrcDirection.dotProduct(xDirection)) < 0.0001f)
                xQuat = Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z);
            else
                xQuat = xSrcDirection.getRotationTo(xDirection);

            xSceneNode->rotate(xQuat);

            // APPLY ROTATE to BulletCom RigidBody
            btTransform xRigidBodyTransform = xRigidBody->getWorldTransform();
            xRigidBodyTransform.setRotation(JGC::Utils::toBtQuaternion(xSceneNode->getOrientation()));
            xRigidBody->setWorldTransform(xRigidBodyTransform);
        }

        btVector3 xEnemyPos;
        xEnemyPos.setX(xRigidBody->getWorldTransform().getOrigin().x());
        xEnemyPos.setY(xRigidBody->getWorldTransform().getOrigin().y());
        xEnemyPos.setZ(0);

        // Move
        if(xEnemyPos.distance(xPlayerPos) > 33.3f)
        {
            Ogre::Vector3 xMoveDirection;
            xMoveDirection = Ogre::Vector3::ZERO;
            xMoveDirection.x = 1;

            // Get Ogre::SceneNode orientation
            btScalar xMoveSpeed = 17;
            Ogre::Real xMove = xMoveSpeed * xTimeSinceLastUpdate;
            Ogre::Vector3 xVector;
            xVector = xMoveDirection * xMove;
            xVector = xSceneNode->getOrientation() * xVector;

            // Move btRigidBody
            xRigidBody->applyCentralImpulse(JGC::Utils::toBtVector3(xVector));
            btVector3 xCurrentVelocity = xRigidBody->getLinearVelocity();
            btScalar xCurrentSpeed = xCurrentVelocity.length();
            if(xCurrentSpeed > xMoveSpeed)
            {
                xCurrentVelocity *= xMoveSpeed/xCurrentSpeed;
                xRigidBody->setLinearVelocity(xCurrentVelocity);
            }

            xRigidBody->activate();
        }

        // Shoot
        if(xEnemyPos.distance(xPlayerPos) <= 50.0f)
        {
            WeaponCom *xWeaponCom;
            xWeaponCom = xEnemysEntitys.at(i)->getComponent<WeaponCom>();

            if(xWeaponCom->mTimeSinceLastShot >= xWeaponCom->mShootDelay)
            {
                QString xBulletName;
                xBulletName = JGC::CountersSystem::instance()->getNameWithSuffix("BulletsCount", "EnemyBullet");

                BulletCom *xBulletCom = PlayWorld::cBulletCom(1, 1);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xBulletCom);

                Ogre::Vector3 xPosObject = xSceneNode->getPosition();
                Ogre::Vector3 xDestinationDot = JGC::Utils::toOgreVector3(xPlayerPos);

                GraphBodyCom* xGraphBodyCom = PlayWorld::cBulletGraphBodyCom("PlayWorld", xBulletName, xPosObject, xDestinationDot);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xGraphBodyCom);

                PhysBodyCom* xPhysBodyCom = PlayWorld::cBulletPhysBodyCom("PlayWorld", PLAYER_GROUP, JGC::Utils::toBtVector3(xPosObject), JGC::Utils::toBtQuaternion(xGraphBodyCom->mSceneNode->getOrientation()));
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xPhysBodyCom);

                SoundBodyCom *xSoundBodyCom;
                xSoundBodyCom = xEnemysEntitys.at(i)->getComponent<SoundBodyCom>();
                xSoundBodyCom->mSoundSource->play();

                xWeaponCom->mTimeSinceLastShot = 0;
            }
            else if(xWeaponCom->mTimeSinceLastShot < xWeaponCom->mShootDelay)
                xWeaponCom->mTimeSinceLastShot += xTimeSinceLastUpdate;
        }
    }
}
