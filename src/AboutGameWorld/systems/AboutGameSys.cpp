#include "AboutGameSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../AboutGameWorld.h"
#include "../components/AboutGameCom.h"

#include "QDebug"

void AboutGameSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xAboutGameEntitys;
    xAboutGameEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::AboutGameNode);

    if(xAboutGameEntitys.size() > 0)
    {
        AboutGameCom *xAboutGameCom;
        xAboutGameCom = xAboutGameEntitys.first()->getComponent<AboutGameCom>();

        if(xAboutGameCom->mBackToMainMenu->isButtonPressed())
            JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
    }
}
