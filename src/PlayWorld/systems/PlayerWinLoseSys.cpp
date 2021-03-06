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
        QList<JGC::Entity*> xEntitys;
        xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::EnemyStatNode);

        if(xEntitys.size() == 0)
        {
            JGC::WorldsSystem::instance()->setActiveWorld("WinWorld");
            return;
        }
    }

    // Check is enemy lose game
    {
        QList<JGC::Entity*> xEntitys;
        xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerStatNode);

        if(xEntitys.size() == 0)
        {
            JGC::WorldsSystem::instance()->setActiveWorld("LoseWorld");
            return;
        }
    }
}
