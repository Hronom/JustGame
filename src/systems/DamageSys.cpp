#include "DamageSys.h"

#include <PhysicsSystem.h>
#include <WorldsSystem.h>
#include "Entity.h"
#include "../components/PhysBody.h"
#include "../components/Health.h"
#include "../components/Bullet.h"

#include <QVector>
#include <QDebug>

void DamageSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xDamageableEntitys;
    xDamageableEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("Damageable");

    QVector<JGC::Entity*> xDoDamageEntitys;
    xDoDamageEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("DoDamage");

    if(xDamageableEntitys.size() > 0 && xDoDamageEntitys.size() > 0)
    {
        QVector<QPair<const btCollisionObject *, const btCollisionObject *> > xCollidedObjects;
        xCollidedObjects = JGC::PhysicsSystem::instance()->getCollidedObjects();

        QVector<QPair<const btCollisionObject *, const btCollisionObject *> >::iterator xIter;
        xIter = xCollidedObjects.begin();
        while(xIter != xCollidedObjects.end())
        {
            PhysBody *xPhysBodyA = static_cast<PhysBody*>(xIter->first->getUserPointer());
            PhysBody *xPhysBodyB = static_cast<PhysBody*>(xIter->second->getUserPointer());

            JGC::Entity *xDamageableEntity = 0;
            JGC::Entity *xDoDamageEntity = 0;

            // Find Damageable entity
            for(int i = 0; i < xDamageableEntitys.size(); ++i)
            {
                PhysBody *xPhysBodyCandidate;
                xPhysBodyCandidate = static_cast<PhysBody*>(xDamageableEntitys.at(i)->getComponent("PhysBody"));

                if (xPhysBodyCandidate == xPhysBodyA ||
                    xPhysBodyCandidate == xPhysBodyB )
                {
                    xDamageableEntity = xDamageableEntitys.at(i);
                    break;
                }
            }

            // Find DoDamage entity
            for(int i = 0; i < xDoDamageEntitys.size(); ++i)
            {
                PhysBody *xPhysBodyCandidate;
                xPhysBodyCandidate = static_cast<PhysBody*>(xDoDamageEntitys.at(i)->getComponent("PhysBody"));

                if (xPhysBodyCandidate == xPhysBodyA ||
                    xPhysBodyCandidate == xPhysBodyB )
                {
                    if(xDoDamageEntity == 0)
                        xDoDamageEntity = xDoDamageEntitys.at(i);
                    /*else
                    {
                        Damage *xDamage;
                        xDamage = static_cast<Damage*>(xDoDamageEntitys.at(i)->getComponent("Damage"));
                        xDamage->mDamageCount = 0;

                        xDamage = static_cast<Damage*>(xDoDamageEntity->getComponent("Damage"));
                        xDamage->mDamageCount = 0;
                    }*/

                }
            }

            // Make damage
            if(xDamageableEntity != 0 && xDoDamageEntity != 0)
            {
                qDebug()<<xDamageableEntity->getName()<<"-"<<xDoDamageEntity->getName();

                // Make damage to entity A
                Health *xHealth;
                xHealth = static_cast<Health*>(xDamageableEntity->getComponent("Health"));

                Bullet *xBullet;
                xBullet = static_cast<Bullet*>(xDoDamageEntity->getComponent("Bullet"));

                xHealth->mHealthCurrent -= xBullet->mDamageCount;
                xBullet->mDamageCount = 0;
            }

            ++xIter;
        }
    }
}
