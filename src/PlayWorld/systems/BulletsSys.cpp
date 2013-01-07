#include "BulletsSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void BulletsSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::BulletsNode);

    QList<JGC::Entity*>::Iterator xEntitysIter;
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        BulletCom *xBulletCom;
        xBulletCom = xEntity->getComponent<BulletCom>();

        if(xBulletCom->mLiveTime >= xBulletCom->mTotalLiveTime || xBulletCom->mDamageCount == 0)
        {
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xBulletCom);

            GraphBodyCom *xGraphBodyCom;
            xGraphBodyCom = xEntity->getComponent<GraphBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xGraphBodyCom);

            PhysBodyCom *xPhysBodyCom;
            xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xPhysBodyCom);

            JGC::WorldsSystem::instance()->getActiveWorld()->removeEntity(xEntity->getName());

            PlayWorld::dGraphBodyCom("PlayWorld", xGraphBodyCom);
            PlayWorld::dPhysBodyCom("PlayWorld", xPhysBodyCom);
            PlayWorld::dBulletCom(xBulletCom);

            JGC::CountersSystem::instance()->removeName("BulletsCount", xEntity->getName());
        }
        else
        {
            xBulletCom->mLiveTime += xTimeSinceLastUpdate;
        }

        ++xEntitysIter;
    }
}
