#include "EnemyDeathSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void EnemyDeathSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

    // Remove enemys that have health <= 0
    QList<JGC::Entity*>::Iterator xEntitysIter;
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        HealthCom *xHealthCom;
        xHealthCom = xEntity->getComponent<HealthCom>();

        if(xHealthCom->mHealthCurrent <= 0)
        {
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xHealthCom);

            GraphBodyCom *xGraphBodyCom;
            xGraphBodyCom = xEntity->getComponent<GraphBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xGraphBodyCom);

            PhysBodyCom *xPhysBodyCom;
            xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntity->getName(), xPhysBodyCom);

            JGC::WorldsSystem::instance()->getActiveWorld()->removeEntity(xEntity->getName());

            PlayWorld::dGraphBodyCom("PlayWorld", xGraphBodyCom);
            PlayWorld::dPhysBodyCom("PlayWorld", xPhysBodyCom);

            JGC::CountersSystem::instance()->removeName("EnemyCount", xEntity->getName());
        }

        ++xEntitysIter;
    }
}
