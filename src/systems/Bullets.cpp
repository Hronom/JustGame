#include "Bullets.h"

#include <EntitySystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../creators/ComponentsCreators.h"

void Bullets::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::EntitySystem::instance()->getEntitysInNode("Bullets");

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        Bullet *xBullet;
        xBullet = static_cast<Bullet*>(xEntitys.at(i)->getComponent("Bullet"));

        if(xBullet->mLiveTime >= xBullet->mTotalLiveTime || xBullet->mDamageCount == 0)
        {
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xBullet);

            GraphBody *xGraphBody;
            xGraphBody = static_cast<GraphBody*>(xEntitys.at(i)->getComponent("GraphBody"));
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xGraphBody);

            PhysBody *xPhysBody;
            xPhysBody = static_cast<PhysBody*>(xEntitys.at(i)->getComponent("PhysBody"));
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xPhysBody);

            JGC::EntitySystem::instance()->removeEntity(xEntitys.at(i)->getName());

            JG::dGraphBody(xGraphBody);
            JG::dPhysBody(xPhysBody);
            JG::dBullet(xBullet);

            JGC::CountersSystem::instance()->removeName("BulletsCount", xEntitys.at(i)->getName());
        }
        else
        {
            xBullet->mLiveTime += xTimeSinceLastUpdate;
        }
    }
}
