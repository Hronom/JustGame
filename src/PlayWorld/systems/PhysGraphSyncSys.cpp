#include "PhysGraphSyncSys.h"

#include <WorldsSystem.h>
#include <Entity.h>

#include <Ogre.h>

#include "../components/GraphBodyCom.h"
#include "../components/PhysBodyCom.h"

void PhysGraphSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysGraphSync);

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = static_cast<GraphBodyCom*>(xEntitys.at(i)->getComponent(ComponentsTypes::GraphBodyCom));

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = static_cast<PhysBodyCom*>(xEntitys.at(i)->getComponent(ComponentsTypes::PhysBodyCom));

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btQuaternion xRot = xWorldTrans.getRotation();
        xGraphBodyCom->mSceneNode->setOrientation(xRot.w(), xRot.x(), xRot.y(), xRot.z());
        btVector3 xPos = xWorldTrans.getOrigin();
        xGraphBodyCom->mSceneNode->setPosition(xPos.x(), xPos.y(), xPos.z());
    }
}
