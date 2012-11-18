#include "PhysGraphSync.h"

#include <Ogre.h>

#include "../components/GraphBody.h"
#include "../components/PhysBody.h"

void PhysGraphSync::proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate)
{
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
