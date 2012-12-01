#include "PlayerGUISys.h"

#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <WorldsSystem.h>
#include "Entity.h"
#include "Utils.h"
#include "../components/Health.h"
#include "../components/PlayerUI.h"
#include "../components/PhysBody.h"

#include <QVector>
#include <QDebug>

void PlayerGUISys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xGUIEntitys;
    xGUIEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("GUI");

    PlayerUI *xGUI;
    if(xGUIEntitys.size() > 0)
    {
        xGUI = static_cast<PlayerUI*>(xGUIEntitys.at(0)->getComponent("PlayerUI"));
        MyGUI::PointerManager::getInstancePtr()->setPointer("Arrow");
        xGUI->mEnemyPanel->setVisible(false);
    }

    // Update player stat
    {
        QVector<JGC::Entity*> xPlayerEntitys;
        xPlayerEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("PlayerStat");

        if(xPlayerEntitys.size() > 0)
        {
            Health *xHealth;
            xHealth = static_cast<Health*>(xPlayerEntitys.at(0)->getComponent("Health"));

            xGUI->mPlayerHealthBar->setProgressRange(xHealth->mHealthTotal);
            xGUI->mPlayerHealthBar->setProgressPosition(xHealth->mHealthCurrent);
        }
    }

    // Update enemy stat
    {
        btVector3 xStartDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(0));
        btVector3 xEndDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(113));// Ѕольше на 13 единиц рассто€ни€ от камеры до 0 по оси Z(чтобы пробило лучом наверн€ка)

        btCollisionWorld::ClosestRayResultCallback xRayCallback(xStartDot, xEndDot);

        // Perform raycast
        JGC::PhysicsSystem::instance()->getDynamicsWorld()->rayTest(xStartDot, xEndDot, xRayCallback);

        if(xRayCallback.hasHit())
        {
            PhysBody *xPhysBody = static_cast<PhysBody*>(xRayCallback.m_collisionObject->getUserPointer());

            QVector<JGC::Entity*> xEnemysEntitys;
            xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("EnemyStat");

            if(xEnemysEntitys.size() > 0)
            {
                for(int i = 0; i < xEnemysEntitys.size(); ++i)
                {
                    PhysBody *xPhysBodyCandidate;
                    xPhysBodyCandidate = static_cast<PhysBody*>(xEnemysEntitys.at(i)->getComponent("PhysBody"));

                    if(xPhysBodyCandidate == xPhysBody)
                    {
                        Health *xHealth;
                        xHealth = static_cast<Health*>(xEnemysEntitys.at(i)->getComponent("Health"));

                        MyGUI::PointerManager::getInstancePtr()->setPointer("hand");
                        xGUI->mEnemyPanel->setVisible(true);
                        xGUI->mEnemyHealthBar->setProgressRange(xHealth->mHealthTotal);
                        xGUI->mEnemyHealthBar->setProgressPosition(xHealth->mHealthCurrent);
                    }
                }
            }
        }
    }
}
