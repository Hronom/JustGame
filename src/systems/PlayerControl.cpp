#include "PlayerControl.h"

#include <InputSystem.h>
#include <GraphicSystem.h>
#include <EntitySystem.h>
#include <IComponent.h>
#include <Utils.h>

#include "QDebug"

#include "../components/GraphBody.h"
#include "../components/PhysBody.h"
#include "../components/Weapon.h"
#include "../components/Bullet.h"

#include "../creators/ComponentsCreators.h"

void PlayerControl::proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate)
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

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        GraphBody *xGraphBody;
        xGraphBody = static_cast<GraphBody*>(xEntitys.at(i)->getComponent("GraphBody"));

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBody->mSceneNode;

        PhysBody *xPhysBody;
        xPhysBody = static_cast<PhysBody*>(xEntitys.at(i)->getComponent("PhysBody"));

        btRigidBody *xRigidBody;
        xRigidBody = xPhysBody->mRigidBody;

        // Get destination dot
        OIS::MouseState xMouseState;
        xMouseState = JGC::InputSystem::instance()->getMouseState();
        Ogre::Ray xMouseRay = JGC::GraphicSystem::instance()->getCamera()->getCameraToViewportRay(xMouseState.X.abs / float(xMouseState.width), xMouseState.Y.abs / float(xMouseState.height));
        Ogre::Vector3 xDestinationDot = xMouseRay.getPoint(100); //почему 100? Расстояние между камерой и нулевой точкой оси z равно 100
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

            // APPLY ROTATE to Bullet RigidBody
            btTransform xRigidBodyTransform = xRigidBody->getWorldTransform();
            xRigidBodyTransform.setRotation(JGC::Utils::toBtQuaternion(xSceneNode->getOrientation()));
            xRigidBody->setWorldTransform(xRigidBodyTransform);
        }

        // Move
        {
            // Get Ogre::SceneNode orientation
            btScalar xMoveSpeed = 7;
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
            Weapon *xWeapon;
            xWeapon = static_cast<Weapon*>(xEntitys.at(i)->getComponent("Weapon"));

            if(xShoot == true && xWeapon->mTimeSinceLastShot >= xWeapon->mShootDelay)
            {
                Bullet *xBullet = JG::cBullet(1);
                JGC::EntitySystem::instance()->addComponent("Bullet", xBullet);

                Ogre::Vector3 xPosObject = xSceneNode->getPosition();
                GraphBody* xGraphBody = JG::cBulletGraphBody("Bullet", xPosObject, xDestinationDot);
                JGC::EntitySystem::instance()->addComponent("Bullet", xGraphBody);

                PhysBody* xPhysBody = JG::cBulletPhysBody(ENEMY_GROUP, JGC::Utils::toBtVector3(xPosObject), JGC::Utils::toBtQuaternion(xGraphBody->mSceneNode->getOrientation()));
                JGC::EntitySystem::instance()->addComponent("Bullet", xPhysBody);

                //mGameObjectsListener->addBullet(ENEMY_GROUP, xPos, xDestinationDot);
                //mSoundSource->move(xPosObject.x,xPosObject.y,xPosObject.z);
                //mSoundSource->play();
                xWeapon->mTimeSinceLastShot = 0;
            }

            if(xWeapon->mTimeSinceLastShot < xWeapon->mShootDelay)
                xWeapon->mTimeSinceLastShot += xTimeSinceLastUpdate;
        }
    }
}
