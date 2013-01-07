#include "PhysSoundSyncSys.h"

#include <WorldsSystem.h>
#include <Entity.h>

#include <Ogre.h>

#include "../components/SoundBodyCom.h"
#include "../components/SoundListenerCom.h"
#include "../components/PhysBodyCom.h"

void PhysSoundSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xEntitys;

    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysSoundSyncNode);
    QList<JGC::Entity*>::Iterator xEntitysIter;
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        SoundBodyCom *xSoundBodyCom;
        xSoundBodyCom = xEntity->getComponent<SoundBodyCom>();

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btVector3 xPos = xWorldTrans.getOrigin();
        xSoundBodyCom->mSoundSource->move(xPos.x(), xPos.y(), xPos.z());

        ++xEntitysIter;
    }

    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PhysSoundListenerSyncNode);
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        SoundListenerCom *xSoundListenerCom;
        xSoundListenerCom = xEntity->getComponent<SoundListenerCom>();

        PhysBodyCom *xPhysBodyCom;
        xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();

        const btTransform &xWorldTrans = xPhysBodyCom->mRigidBody->getWorldTransform();
        btVector3 xPos = xWorldTrans.getOrigin();
        xSoundListenerCom->mSoundListener->move(xPos.x(), xPos.y(), xPos.z());

        ++xEntitysIter;
    }
}
