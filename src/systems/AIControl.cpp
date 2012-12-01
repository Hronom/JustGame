#include "AIControl.h"

#include <InputSystem.h>
#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <IComponent.h>
#include <Utils.h>
#include <Entity.h>

#include "QDebug"

#include "../creators/ComponentsCreators.h"

AIControl::AIControl()
{
    JGC::CountersSystem::instance()->addCounter("BulletsCount");
}

void AIControl::injectUpdate(const float &xTimeSinceLastUpdate)
{
    btVector3 xPlayerPos;
    xPlayerPos.setZero();

    // Get player pos
    {
        QVector<JGC::Entity*> xPlayersEntitys;
        xPlayersEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("PlayerControl");

        if(xPlayersEntitys.size()>0)
        {
            PhysBody *xPlayerPhysBody;
            xPlayerPhysBody = static_cast<PhysBody*>(xPlayersEntitys.at(0)->getComponent("PhysBody"));

            xPlayerPos.setX(xPlayerPhysBody->mRigidBody->getWorldTransform().getOrigin().x());
            xPlayerPos.setY(xPlayerPhysBody->mRigidBody->getWorldTransform().getOrigin().y());
            xPlayerPos.setZ(0);
        }
    }



    QVector<JGC::Entity*> xEnemysEntitys;
    xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("AIControl");

    for(int i = 0; i < xEnemysEntitys.size(); ++i)
    {
        Health *xHealth;
        xHealth = static_cast<Health*>(xEnemysEntitys.at(i)->getComponent("Health"));
        qDebug()<<"Enemy"<<xHealth->mHealthCurrent<<xHealth->mHealthTotal;

        GraphBody *xGraphBody;
        xGraphBody = static_cast<GraphBody*>(xEnemysEntitys.at(i)->getComponent("GraphBody"));

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBody->mSceneNode;

        PhysBody *xPhysBody;
        xPhysBody = static_cast<PhysBody*>(xEnemysEntitys.at(i)->getComponent("PhysBody"));

        btRigidBody *xRigidBody;
        xRigidBody = xPhysBody->mRigidBody;

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

            // APPLY ROTATE to Bullet RigidBody
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
            Weapon *xWeapon;
            xWeapon = static_cast<Weapon*>(xEnemysEntitys.at(i)->getComponent("Weapon"));

            if(xWeapon->mTimeSinceLastShot >= xWeapon->mShootDelay)
            {                
                QString xBulletName;
                xBulletName = JGC::CountersSystem::instance()->getNameWithSuffix("BulletsCount", "EnemyBullet");

                Bullet *xBullet = JG::cBullet(1, 1);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xBullet);

                Ogre::Vector3 xPosObject = xSceneNode->getPosition();
                Ogre::Vector3 xDestinationDot = JGC::Utils::toOgreVector3(xPlayerPos);

                GraphBody* xGraphBody = JG::cBulletGraphBody("PlayWorld", xBulletName, xPosObject, xDestinationDot);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xGraphBody);

                PhysBody* xPhysBody = JG::cBulletPhysBody(PLAYER_GROUP, JGC::Utils::toBtVector3(xPosObject), JGC::Utils::toBtQuaternion(xGraphBody->mSceneNode->getOrientation()));
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xPhysBody);

                //mGameObjectsListener->addBullet(ENEMY_GROUP, xPos, xDestinationDot);
                //mSoundSource->move(xPosObject.x,xPosObject.y,xPosObject.z);
                //mSoundSource->play();
                xWeapon->mTimeSinceLastShot = 0;
            }
            else if(xWeapon->mTimeSinceLastShot < xWeapon->mShootDelay)
                xWeapon->mTimeSinceLastShot += xTimeSinceLastUpdate;
        }
    }
}
