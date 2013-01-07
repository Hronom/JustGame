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
    QList<JGC::Entity*> xDamageableEntitys;
    xDamageableEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::DamageableNode);

    QList<JGC::Entity*> xDoDamageEntitys;
    xDoDamageEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::DoDamageNode);

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


            QList<JGC::Entity*>::Iterator xEntitysIter;

            // Find DamageableNode entity
            xEntitysIter = xDamageableEntitys.begin();
            while(xEntitysIter != xDamageableEntitys.end())
            {
                JGC::Entity *xEntity;
                xEntity = (*xEntitysIter);

                PhysBodyCom *xPhysBodyCandidate;
                xPhysBodyCandidate = xEntity->getComponent<PhysBodyCom>();

                if (xPhysBodyCandidate == xPhysBodyA ||
                    xPhysBodyCandidate == xPhysBodyB )
                {
                    xDamageableEntity = xEntity;
                    break;
                }

                ++xEntitysIter;
            }

            // Find DoDamageNode entity
            xEntitysIter = xDoDamageEntitys.begin();
            while(xEntitysIter != xDoDamageEntitys.end())
            {
                JGC::Entity *xEntity;
                xEntity = (*xEntitysIter);

                PhysBodyCom *xPhysBodyCandidate;
                xPhysBodyCandidate = xEntity->getComponent<PhysBodyCom>();

                if (xPhysBodyCandidate == xPhysBodyA ||
                    xPhysBodyCandidate == xPhysBodyB )
                {
                    if(xDoDamageEntity == 0)
                        xDoDamageEntity = xEntity;
                }

                ++xEntitysIter;
            }

            // Make damage
            if(xDamageableEntity != 0 && xDoDamageEntity != 0)
            {
                // Make damage to entity A
                HealthCom *xHealthCom;
                xHealthCom = xDamageableEntity->getComponent<HealthCom>();

                BulletCom *xBulletCom;
                xBulletCom = xDoDamageEntity->getComponent<BulletCom>();

                xHealthCom->mHealthCurrent -= xBulletCom->mDamageCount;
                xBulletCom->mDamageCount = 0;
            }

            ++xIter;
        }
    }
}
