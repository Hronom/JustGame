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
    QVector<JGC::Entity*> xGameGUIEntitys;
    xGameGUIEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::GameGUINode);

    PlayerUICom *xPlayerUICom;
    if(xGameGUIEntitys.size() > 0)
    {
        xPlayerUICom = static_cast<PlayerUICom*>(xGameGUIEntitys.at(0)->getComponent(Components::PlayerUICom));
        MyGUI::PointerManager::getInstancePtr()->setPointer("Arrow");
        xPlayerUICom->mEnemyPanel->setVisible(false);
    }

    // Update player stat
    {
        QVector<JGC::Entity*> xPlayerEntitys;
        xPlayerEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerStatNode);

        if(xPlayerEntitys.size() > 0)
        {
            HealthCom *xHealthCom;
            xHealthCom = static_cast<HealthCom*>(xPlayerEntitys.at(0)->getComponent(Components::HealthCom));

            xPlayerUICom->mPlayerHealthBar->setProgressRange(xHealthCom->mHealthTotal);
            xPlayerUICom->mPlayerHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
        }
    }

    // Update enemy stat
    {
        btVector3 xStartDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(0));
        btVector3 xEndDot = JGC::Utils::toBtVector3(JGC::GraphicSystem::instance()->getMouseWorldCoord(113));// ������ �� 13 ������ ���������� �� ������ �� 0 �� ��� Z(����� ������� ����� ���������)

        btCollisionWorld::ClosestRayResultCallback xRayCallback(xStartDot, xEndDot);

        // Perform raycast
        JGC::PhysicsSystem::instance()->getDynamicsWorld("PlayWorld")->rayTest(xStartDot, xEndDot, xRayCallback);

        if(xRayCallback.hasHit())
        {
            PhysBodyCom *xPhysBodyCom = static_cast<PhysBodyCom*>(xRayCallback.m_collisionObject->getUserPointer());

            QVector<JGC::Entity*> xEnemysEntitys;
            xEnemysEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

            if(xEnemysEntitys.size() > 0)
            {
                for(int i = 0; i < xEnemysEntitys.size(); ++i)
                {
                    PhysBodyCom *xPhysBodyCandidate;
                    xPhysBodyCandidate = static_cast<PhysBodyCom*>(xEnemysEntitys.at(i)->getComponent(Components::PhysBodyCom));

                    if(xPhysBodyCandidate == xPhysBodyCom)
                    {
                        HealthCom *xHealthCom;
                        xHealthCom = static_cast<HealthCom*>(xEnemysEntitys.at(i)->getComponent(Components::HealthCom));

                        MyGUI::PointerManager::getInstancePtr()->setPointer("hand");
                        xPlayerUICom->mEnemyPanel->setVisible(true);
                        xPlayerUICom->mEnemyHealthBar->setProgressRange(xHealthCom->mHealthTotal);
                        xPlayerUICom->mEnemyHealthBar->setProgressPosition(xHealthCom->mHealthCurrent);
                    }
                }
            }
        }
    }
}
