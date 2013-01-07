#include "PhysGraphSyncSys.h"

#include <WorldsSystem.h>
#include <Entity.h>

#include <Ogre.h>

#include "../components/GraphBodyCom.h"
#include "../components/PhysBodyCom.h"

void PhysGraphSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysGraphSyncNode);

    QList<JGC::Entity*>::Iterator xEntitysIter;
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = xEntity->getComponent<GraphBodyCom>();

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btQuaternion xRot = xWorldTrans.getRotation();
        xGraphBodyCom->mSceneNode->setOrientation(xRot.w(), xRot.x(), xRot.y(), xRot.z());
        btVector3 xPos = xWorldTrans.getOrigin();
        xGraphBodyCom->mSceneNode->setPosition(xPos.x(), xPos.y(), xPos.z());

        ++xEntitysIter;
    }
}
