#include "DamageSys.h"

#include <PhysicsSystem.h>
#include <WorldsSystem.h>
#include "Entity.h"
#include "../components/PhysBodyCom.h"
#include "../components/HealthCom.h"
#include "../components/BulletCom.h"

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
            PhysBodyCom *xPhysBodyA = static_cast<PhysBodyCom*>(xIter->first->getUserPointer());
            PhysBodyCom *xPhysBodyB = static_cast<PhysBodyCom*>(xIter->second->getUserPointer());

            JGC::Entity *xDamageableEntity = 0;
            JGC::Entity *xDoDamageEntity = 0;

            // Find Damageable entity
            for(int i = 0; i < xDamageableEntitys.size(); ++i)
            {
                PhysBodyCom *xPhysBodyCandidate;
                xPhysBodyCandidate = static_cast<PhysBodyCom*>(xDamageableEntitys.at(i)->getComponent("PhysBodyCom"));

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
                PhysBodyCom *xPhysBodyCandidate;
                xPhysBodyCandidate = static_cast<PhysBodyCom*>(xDoDamageEntitys.at(i)->getComponent("PhysBodyCom"));

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
                HealthCom *xHealthCom;
                xHealthCom = static_cast<HealthCom*>(xDamageableEntity->getComponent("HealthCom"));

                BulletCom *xBulletCom;
                xBulletCom = static_cast<BulletCom*>(xDoDamageEntity->getComponent("BulletCom"));

                xHealthCom->mHealthCurrent -= xBulletCom->mDamageCount;
                xBulletCom->mDamageCount = 0;
            }

            ++xIter;
        }
    }
}
