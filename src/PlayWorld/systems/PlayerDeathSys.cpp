#include "PlayerDeathSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void PlayerDeathSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerStatNode);

    // Remove enemys that have health <= 0
    for(int i = 0; i < xEntitys.size(); ++i)
    {
        HealthCom *xHealthCom;
        xHealthCom = xEntitys.at(i)->getComponent<HealthCom>();

        if(xHealthCom->mHealthCurrent <= 0)
        {
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xHealthCom);

            GraphBodyCom *xGraphBodyCom;
            xGraphBodyCom = xEntitys.at(i)->getComponent<GraphBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xGraphBodyCom);

            PhysBodyCom *xPhysBodyCom;
            xPhysBodyCom = xEntitys.at(i)->getComponent<PhysBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xPhysBodyCom);

            JGC::WorldsSystem::instance()->getActiveWorld()->removeEntity(xEntitys.at(i)->getName());

            PlayWorld::dGraphBodyCom("PlayWorld", xGraphBodyCom);
            PlayWorld::dPhysBodyCom("PlayWorld", xPhysBodyCom);

            xEntitys.remove(i);
        }
    }
}
