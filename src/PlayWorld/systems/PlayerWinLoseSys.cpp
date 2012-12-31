#include "PlayerWinLoseSys.h"

#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

void PlayerWinLoseSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    // Check is player win game
    {
        QVector<JGC::Entity*> xEntitys;
        xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

        if(xEntitys.size() == 0)
        {
            JGC::WorldsSystem::instance()->loadWorld("WinWorld");
            //JGC::WorldsSystem::instance()->getWorld("MainMenuWorld")->removeComponent("MainMenuEntity", xMainMenuCom);
            //MainMenuWorld::dMainMenuCom(xMainMenuCom);
            JGC::WorldsSystem::instance()->setActiveWorld("WinWorld");
            return;
        }
    }

    // Check is enemy lose game
    {
        QVector<JGC::Entity*> xEntitys;
        xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerStatNode);

        if(xEntitys.size() == 0)
        {
            JGC::WorldsSystem::instance()->loadWorld("LoseWorld");
            JGC::WorldsSystem::instance()->setActiveWorld("LoseWorld");
            return;
        }
    }
}
