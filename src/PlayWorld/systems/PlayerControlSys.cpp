#include "PlayerControlSys.h"

#include <InputSystem.h>
#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <IComponent.h>
#include <Utils.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

PlayerControlSys::PlayerControlSys()
{
    JGC::CountersSystem::instance()->addCounter("BulletsCount");
}

void PlayerControlSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    Ogre::Vector3 xMoveDirection = Ogre::Vector3::ZERO;

    if(JGC::InputSystem::instance()->isKeyDown(OIS::KC_W))
        xMoveDirection.x = 1;

    if(JGC::InputSystem::instance()->isKeyDown(OIS::KC_S))
        xMoveDirection.x = -1;

    if(JGC::InputSystem::instance()->isKeyDown(OIS::KC_A))
        xMoveDirection.y = 1;

    if(JGC::InputSystem::instance()->isKeyDown(OIS::KC_D))
        xMoveDirection.y = -1;

    bool xShoot = false;
    if(JGC::InputSystem::instance()->isKeyDown(OIS::MB_Left))
        xShoot = true;

    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerControlNode);

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        HealthCom *xHealthCom;
        xHealthCom = xEntitys.at(i)->getComponent<HealthCom>();

        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = xEntitys.at(i)->getComponent<GraphBodyCom>();

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBodyCom->mSceneNode;

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntitys.at(i)->getComponent<PhysBodyCom>();

        btRigidBody *xRigidBody;
        xRigidBody = xPhysBodyCom->mRigidBody;

        // Get destination dot
        Ogre::Vector3 xDestinationDot = JGC::GraphicSystem::instance()->getMouseWorldCoord(100); //почему 100? Расстояние между камерой и нулевой точкой оси z равно 100
        xDestinationDot.z = 0;

        // Rotate
        {
            // ROTATE Ogre SceneNode
            Ogre::Vector3 xDirection = xDestinationDot - xSceneNode->getPosition();
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

        // Move
        {
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
        {
            WeaponCom *xWeaponCom;
            xWeaponCom = xEntitys.at(i)->getComponent<WeaponCom>();

            if(xShoot == true && xWeaponCom->mTimeSinceLastShot >= xWeaponCom->mShootDelay)
            {
                QString xBulletName;
                xBulletName = JGC::CountersSystem::instance()->getNameWithSuffix("BulletsCount", "PlayerBullet");

                BulletCom *xBulletCom = PlayWorld::cBulletCom(1, 1);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xBulletCom);

                Ogre::Vector3 xPosObject = xSceneNode->getPosition();

                GraphBodyCom* xGraphBodyCom = PlayWorld::cBulletGraphBodyCom("PlayWorld", xBulletName, xPosObject, xDestinationDot);
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xGraphBodyCom);

                PhysBodyCom* xPhysBodyCom = PlayWorld::cBulletPhysBodyCom("PlayWorld", ENEMY_GROUP, JGC::Utils::toBtVector3(xPosObject), JGC::Utils::toBtQuaternion(xGraphBodyCom->mSceneNode->getOrientation()));
                JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xBulletName, xPhysBodyCom);

                //mGameObjectsListener->addBullet(ENEMY_GROUP, xPos, xDestinationDot);
                //mSoundSource->move(xPosObject.x,xPosObject.y,xPosObject.z);
                //mSoundSource->play();
                xWeaponCom->mTimeSinceLastShot = 0;
            }
            else if(xWeaponCom->mTimeSinceLastShot < xWeaponCom->mShootDelay)
                xWeaponCom->mTimeSinceLastShot += xTimeSinceLastUpdate;
        }
    }
}
