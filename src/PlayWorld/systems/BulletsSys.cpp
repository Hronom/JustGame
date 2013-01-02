#include "BulletsSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void BulletsSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::BulletsNode);

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        BulletCom *xBulletCom;
        xBulletCom = xEntitys.at(i)->getComponent<BulletCom>();

        if(xBulletCom->mLiveTime >= xBulletCom->mTotalLiveTime || xBulletCom->mDamageCount == 0)
        {
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xBulletCom);

            GraphBodyCom *xGraphBodyCom;
            xGraphBodyCom = xEntitys.at(i)->getComponent<GraphBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xGraphBodyCom);

            PhysBodyCom *xPhysBodyCom;
            xPhysBodyCom = xEntitys.at(i)->getComponent<PhysBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xPhysBodyCom);

            JGC::WorldsSystem::instance()->getActiveWorld()->removeEntity(xEntitys.at(i)->getName());

            PlayWorld::dGraphBodyCom("PlayWorld", xGraphBodyCom);
            PlayWorld::dPhysBodyCom("PlayWorld", xPhysBodyCom);
            PlayWorld::dBulletCom(xBulletCom);

            JGC::CountersSystem::instance()->removeName("BulletsCount", xEntitys.at(i)->getName());
        }
        else
        {
            xBulletCom->mLiveTime += xTimeSinceLastUpdate;
        }
    }
}
