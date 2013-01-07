#include "MainMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../MainMenuWorld.h"
#include "../components/MainMenuCom.h"

#include "QDebug"

void MainMenuSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xMainMenuEntitys;
    xMainMenuEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::MainMenuNode);

    if(xMainMenuEntitys.size() > 0)
    {
        MainMenuCom *xMainMenuCom;
        xMainMenuCom = xMainMenuEntitys.first()->getComponent<MainMenuCom>();

        if(xMainMenuCom->mNewGameButton->isButtonPressed())
        {
            JGC::WorldsSystem::instance()->setActiveWorld("PlayWorld");
            return;
        }

        if(xMainMenuCom->mAboutProgram->isButtonPressed())
        {
            JGC::WorldsSystem::instance()->setActiveWorld("AboutGameWorld");
            return;
        }

        if(xMainMenuCom->mExitButton->isButtonPressed())
        {
            JGC::MainSystem::instance()->needShutdown();
            return;
        }
    }
}
