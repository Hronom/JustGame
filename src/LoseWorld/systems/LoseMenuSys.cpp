#include "LoseMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../LoseWorld.h"
#include "../components/LoseMenuCom.h"

#include "QDebug"

void LoseMenuSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xLoseMenuEntitys;
    xLoseMenuEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::LoseMenuNode);

    if(xLoseMenuEntitys.size() > 0)
    {
        LoseMenuCom *xLoseMenuCom;
        xLoseMenuCom = xLoseMenuEntitys.first()->getComponent<LoseMenuCom>();

        if(xLoseMenuCom->mLoseOkButton->isButtonPressed())                
            JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
    }
}
