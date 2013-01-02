#include "WinMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../WinWorld.h"
#include "../components/WinMenuCom.h"

#include "QDebug"

void WinMenuSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xWinMenuEntitys;
    xWinMenuEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::WinMenuNode);

    if(xWinMenuEntitys.size() > 0)
    {
        WinMenuCom *xWinMenuCom;
        xWinMenuCom = xWinMenuEntitys.at(0)->getComponent<WinMenuCom>();

        if(xWinMenuCom->mWinOkButton->isButtonPressed())               
            JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
    }
}
