#include "PlayerGUISys.h"

#include "PhysicsSystem.h"
#include "EntitySystem.h"
#include "InputSystem.h"
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
    xGUIEntitys = JGC::EntitySystem::instance()->getEntitysInNode("GUI");

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
        xPlayerEntitys = JGC::EntitySystem::instance()->getEntitysInNode("PlayerStat");

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
        OIS::MouseState xMouseState;
        xMouseState = JGC::InputSystem::instance()->getMouseState();
        Ogre::Ray xMouseRay = JGC::GraphicSystem::instance()->getCamera()->getCameraToViewportRay(xMouseState.X.abs / float(xMouseState.width), xMouseState.Y.abs / float(xMouseState.height));

        btVector3 xStartDot = JGC::Utils::toBtVector3(xMouseRay.getPoint(0));
        btVector3 xEndDot = JGC::Utils::toBtVector3(xMouseRay.getPoint(113));// ������ �� 13 ������ ���������� �� ������ �� 0 �� ��� Z(����� ������� ����� ���������)

        btCollisionWorld::ClosestRayResultCallback xRayCallback(xStartDot, xEndDot);

        // Perform raycast
        JGC::PhysicsSystem::instance()->getDynamicsWorld()->rayTest(xStartDot, xEndDot, xRayCallback);

        if(xRayCallback.hasHit())
        {
            PhysBody *xPhysBody = static_cast<PhysBody*>(xRayCallback.m_collisionObject->getUserPointer());

            QVector<JGC::Entity*> xEnemysEntitys;
            xEnemysEntitys = JGC::EntitySystem::instance()->getEntitysInNode("EnemyStat");

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
