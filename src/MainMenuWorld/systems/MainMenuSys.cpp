#include "MainMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../creators/ComponentsCreators.h"
#include "../components/MainMenuCom.h"

#include "QDebug"

MainMenuSys::MainMenuSys()
{

}

void MainMenuSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xMainMenuEntitys;
    xMainMenuEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode("MainMenu");

    if(xMainMenuEntitys.size()>0)
    {
        MainMenuCom *xMainMenuCom;
        xMainMenuCom = static_cast<MainMenuCom*>(xMainMenuEntitys.at(0)->getComponent("MainMenuCom"));

        if(xMainMenuCom->mNewGameButton->isButtonPressed())
        {
            JGC::WorldsSystem::instance()->loadWorld("PlayWorld");
            JGC::WorldsSystem::instance()->getWorld("MainMenuWorld")->removeComponent("MainMenuEntity", xMainMenuCom);
            JG::dMainMenuCom(xMainMenuCom);
            JGC::WorldsSystem::instance()->setActiveWorld("PlayWorld");
        }

        if(xMainMenuCom->mExitButton->isButtonPressed())
            JGC::MainSystem::instance()->needShutdown();
    }
}
