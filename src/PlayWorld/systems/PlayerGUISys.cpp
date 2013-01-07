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
    QList<JGC::Entity*> xGameGUIEntitys;
    xGameGUIEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::GameGUINode);

    PlayerUICom *xPlayerUICom;
    if(xGameGUIEntitys.size() > 0)
    {
        xPlayerUICom = xGameGUIEntitys.first()->getComponent<PlayerUICom>();
        MyGUI::PointerManager::getInstancePtr()->setPointer("Arrow");
        xPlayerUICom->mEnemyPanel->setVisible(false);
    }

    // Update player stat
    {
        QList<JGC::Entity*> xPlayerEntitys;
        xPlayerEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerStatNode);

        if(xPlayerEntitys.size() > 0)
        {
            HealthCom *xHealthCom;
            xHealthCom = xPlayerEntitys.first()->getComponent<HealthCom>();

            xPlayerUICom->mPlayerHealthBar->setProgressRange(xHealthCom->mHealthTotal);
            xPlayerUICom->mPlayerHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
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

            QList<JGC::Entity*> xEnemysEntitys;
            xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

            if(xEnemysEntitys.size() > 0)
            {
                QList<JGC::Entity*>::Iterator xEntitysIter;
                xEntitysIter = xEnemysEntitys.begin();
                while(xEntitysIter != xEnemysEntitys.end())
                {
                    JGC::Entity *xEntity;
                    xEntity = (*xEntitysIter);

                    PhysBodyCom *xPhysBodyCandidate;
                    xPhysBodyCandidate = xEntity->getComponent<PhysBodyCom>();

                    if(xPhysBodyCandidate == xPhysBodyCom)
                    {
                        HealthCom *xHealthCom;
                        xHealthCom = xEntity->getComponent<HealthCom>();

                        MyGUI::PointerManager::getInstancePtr()->setPointer("hand");
                        xPlayerUICom->mEnemyPanel->setVisible(true);
                        xPlayerUICom->mEnemyHealthBar->setProgressRange(xHealthCom->mHealthTotal);
                        xPlayerUICom->mEnemyHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
                    }

                    ++xEntitysIter;
                }
            }
        }
    }
}
