#include "PlayerGUISys.h"


#include "PhysicsSystem.h"
#include "EntitySystem.h"
#include "Entity.h"
#include "../components/Health.h"
#include "../components/PlayerUI.h"
#include "../components/GraphBody.h"

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
        MyGUI::PointerManager::getInstancePtr()->setPointer("arrow");
        MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstancePtr()->getMousePosition();
        MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
        Ogre::Ray ray = JGC::GraphicSystem::instance()->getCamera()->getCameraToViewportRay(xMousePosition.left/float(xSize.width), xMousePosition.top/float(xSize.height));
        Ogre::RaySceneQuery *xRaySceneQuery;
        xRaySceneQuery = JGC::GraphicSystem::instance()->getSceneManager()->createRayQuery(Ogre::Ray());
        xRaySceneQuery->setRay(ray);
        xRaySceneQuery->setSortByDistance(true);
        xRaySceneQuery->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
        Ogre::RaySceneQueryResult& xResult = xRaySceneQuery->execute();

        for(Ogre::RaySceneQueryResult::iterator xIter = xResult.begin(); xIter != xResult.end(); ++xIter)
        {
            if(xIter->movable != 0)
            {
                Ogre::Any xAny = xIter->movable->getUserAny();

                GraphBody *xGraphBody = 0;
                try
                {
                   xGraphBody = Ogre::any_cast<GraphBody*>(xAny);
                }
                catch(Ogre::Exception xException)
                { }

                if(xGraphBody != 0)
                {
                    MyGUI::PointerManager::getInstancePtr()->setPointer("hand");

                    QVector<JGC::Entity*> xEnemysEntitys;
                    xEnemysEntitys = JGC::EntitySystem::instance()->getEntitysInNode("EnemyStat");

                    if(xEnemysEntitys.size() > 0)
                    {
                        for(int i = 0; i < xEnemysEntitys.size(); ++i)
                        {
                            GraphBody *xGraphBodyCandidate;
                            xGraphBodyCandidate = static_cast<GraphBody*>(xEnemysEntitys.at(i)->getComponent("GraphBody"));

                            if(xGraphBodyCandidate == xGraphBody)
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

        JGC::GraphicSystem::instance()->getSceneManager()->destroyQuery(xRaySceneQuery);
    }
}
