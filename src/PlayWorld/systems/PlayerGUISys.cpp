#include "PlayerGUISys.h"

#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <WorldsSystem.h>
#include "Entity.h"
#include "Utils.h"
#include "../components/HealthCom.h"
#include "../components/PlayerUICom.h"
#include "../components/PhysBodyCom.h"

#include <QVector>
#include <QDebug>

void PlayerGUISys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xGUIEntitys;
    xGUIEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("GUI");

    PlayerUICom *xGUI;
    if(xGUIEntitys.size() > 0)
    {
        xGUI = static_cast<PlayerUICom*>(xGUIEntitys.at(0)->getComponent("PlayerUI"));
        MyGUI::PointerManager::getInstancePtr()->setPointer("Arrow");
        xGUI->mEnemyPanel->setVisible(false);
    }

    // Update player stat
    {
        QVector<JGC::Entity*> xPlayerEntitys;
        xPlayerEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("PlayerStat");

        if(xPlayerEntitys.size() > 0)
        {
            HealthCom *xHealthCom;
            xHealthCom = static_cast<HealthCom*>(xPlayerEntitys.at(0)->getComponent("HealthCom"));

            xGUI->mPlayerHealthBar->setProgressRange(xHealthCom->mHealthTotal);
            xGUI->mPlayerHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
        }
    }

    // Update enemy stat
    {
        btVector3 xStartDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(0));
        btVector3 xEndDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(113));// Ѕольше на 13 единиц рассто€ни€ от камеры до 0 по оси Z(чтобы пробило лучом наверн€ка)

        btCollisionWorld::ClosestRayResultCallback xRayCallback(xStartDot, xEndDot);

        // Perform raycast
        JGC::PhysicsSystem::instance()->getDynamicsWorld("PlayWorld")->rayTest(xStartDot, xEndDot, xRayCallback);

        if(xRayCallback.hasHit())
        {
            PhysBodyCom *xPhysBodyCom = static_cast<PhysBodyCom*>(xRayCallback.m_collisionObject->getUserPointer());

            QVector<JGC::Entity*> xEnemysEntitys;
            xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("EnemyStat");

            if(xEnemysEntitys.size() > 0)
            {
                for(int i = 0; i < xEnemysEntitys.size(); ++i)
                {
                    PhysBodyCom *xPhysBodyCandidate;
                    xPhysBodyCandidate = static_cast<PhysBodyCom*>(xEnemysEntitys.at(i)->getComponent("PhysBodyCom"));

                    if(xPhysBodyCandidate == xPhysBodyCom)
                    {
                        HealthCom *xHealthCom;
                        xHealthCom = static_cast<HealthCom*>(xEnemysEntitys.at(i)->getComponent("HealthCom"));

                        MyGUI::PointerManager::getInstancePtr()->setPointer("hand");
                        xGUI->mEnemyPanel->setVisible(true);
                        xGUI->mEnemyHealthBar->setProgressRange(xHealthCom->mHealthTotal);
                        xGUI->mEnemyHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
                    }
                }
            }
        }
    }
}
