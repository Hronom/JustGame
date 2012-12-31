#include "LoseMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../LoseWorld.h"
#include "../components/LoseMenuCom.h"

#include "QDebug"

void LoseMenuSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xLoseMenuEntitys;
    xLoseMenuEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::LoseMenuNode);

    if(xLoseMenuEntitys.size() > 0)
    {
        LoseMenuCom *xLoseMenuCom;
        xLoseMenuCom = static_cast<LoseMenuCom*>(xLoseMenuEntitys.at(0)->getComponent(Components::LoseMenuCom));

        if(xLoseMenuCom->mLoseOkButton->isButtonPressed())
        {                
            JGC::WorldsSystem::instance()->loadWorld("MainMenuWorld");
            JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
        }
    }
}
