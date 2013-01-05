#include "PhysSoundSyncSys.h"

#include <WorldsSystem.h>
#include <Entity.h>

#include <Ogre.h>

#include "../components/SoundBodyCom.h"
#include "../components/SoundListenerCom.h"
#include "../components/PhysBodyCom.h"

void PhysSoundSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;

    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysSoundSyncNode);
    for(int i = 0; i < xEntitys.size(); ++i)
    {
        SoundBodyCom *xSoundBodyCom;
        xSoundBodyCom = xEntitys.at(i)->getComponent<SoundBodyCom>();

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntitys.at(i)->getComponent<PhysBodyCom>();

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btVector3 xPos = xWorldTrans.getOrigin();
        xSoundBodyCom->mSoundSource->move(xPos.x(), xPos.y(), xPos.z());
    }

    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysSoundListenerSyncNode);
    for(int i = 0; i < xEntitys.size(); ++i)
    {
        SoundListenerCom *xSoundListenerCom;
        xSoundListenerCom = xEntitys.at(i)->getComponent<SoundListenerCom>();

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntitys.at(i)->getComponent<PhysBodyCom>();

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btVector3 xPos = xWorldTrans.getOrigin();
        xSoundListenerCom->mSoundListener->move(xPos.x(), xPos.y(), xPos.z());
    }
}
