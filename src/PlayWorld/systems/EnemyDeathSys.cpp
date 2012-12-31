#include "EnemyDeathSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void EnemyDeathSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

    // Remove enemys that have health <= 0
    for(int i = 0; i < xEntitys.size(); ++i)
    {
        HealthCom *xHealthCom;
        xHealthCom = static_cast<HealthCom*>(xEntitys.at(i)->getComponent(Components::HealthCom));

        if(xHealthCom->mHealthCurrent <= 0)
        {
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xHealthCom);

            GraphBodyCom *xGraphBodyCom;
            xGraphBodyCom = static_cast<GraphBodyCom*>(xEntitys.at(i)->getComponent(Components::GraphBodyCom));
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xGraphBodyCom);

            PhysBodyCom *xPhysBodyCom;
            xPhysBodyCom = static_cast<PhysBodyCom*>(xEntitys.at(i)->getComponent(Components::PhysBodyCom));
            JGC::WorldsSystem::instance()->getActiveWorld()->removeComponent(xEntitys.at(i)->getName(), xPhysBodyCom);

            JGC::WorldsSystem::instance()->getActiveWorld()->removeEntity(xEntitys.at(i)->getName());

            PlayWorld::dGraphBodyCom("PlayWorld", xGraphBodyCom);
            PlayWorld::dPhysBodyCom("PlayWorld", xPhysBodyCom);

            xEntitys.remove(i);
            qDebug()<<"Enemy removed";
        }
    }
}
