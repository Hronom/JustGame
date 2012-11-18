#include "Bullets.h"

#include <EntitySystem.h>

#include "QDebug"

#include "../components/Bullet.h"

#include "../creators/ComponentsCreators.h"

void Bullets::proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate)
{
    for(int i = 0; i < xEntitys.size(); ++i)
    {
        Bullet *xBullet;
        xBullet = static_cast<Bullet*>(xEntitys.at(i)->getComponent("Bullet"));

        if(xBullet->mLiveTime >= xBullet->mTotalLiveTime)
        {
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xBullet);

            GraphBody *xGraphBody;
            xGraphBody = static_cast<GraphBody*>(xEntitys.at(i)->getComponent("GraphBody"));
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xGraphBody);

            PhysBody *xPhysBody;
            xPhysBody = static_cast<PhysBody*>(xEntitys.at(i)->getComponent("PhysBody"));
            JGC::EntitySystem::instance()->removeComponent(xEntitys.at(i)->getName(), xPhysBody);

            JGC::EntitySystem::instance()->removeEntity(xEntitys.at(i)->getName());

            JG::dBulletGraphBody(xGraphBody);
            JG::dPhysBody(xPhysBody);
            JG::dBullet(xBullet);
        }
        else
        {
            xBullet->mLiveTime += xTimeSinceLastUpdate;
        }
    }
}
