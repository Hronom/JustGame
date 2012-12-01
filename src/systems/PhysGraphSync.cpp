#include "PhysGraphSync.h"

#include <WorldsSystem.h>
#include <Entity.h>

#include <Ogre.h>

#include "../components/GraphBody.h"
#include "../components/PhysBody.h"

void PhysGraphSync::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("PhysGraphSync");

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        GraphBody *xGraphBody;
        xGraphBody = static_cast<GraphBody*>(xEntitys.at(i)->getComponent("GraphBody"));

        PhysBody *xPhysBody;
        xPhysBody = static_cast<PhysBody*>(xEntitys.at(i)->getComponent("PhysBody"));

        const btTransform &xWorldTrans = xPhysBody->mRigidBody->getWorldTransform();
        btQuaternion xRot = xWorldTrans.getRotation();
        xGraphBody->mSceneNode->setOrientation(xRot.w(), xRot.x(), xRot.y(), xRot.z());
        btVector3 xPos = xWorldTrans.getOrigin();
        xGraphBody->mSceneNode->setPosition(xPos.x(), xPos.y(), xPos.z());
    }
}
