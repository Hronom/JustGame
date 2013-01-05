#include "AboutGameSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>

#include "../AboutGameWorld.h"
#include "../components/AboutGameCom.h"

#include "QDebug"

void AboutGameSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xAboutGameEntitys;
    xAboutGameEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::AboutGameNode);

    if(xAboutGameEntitys.size()>0)
    {
        AboutGameCom *xAboutGameCom;
        xAboutGameCom = xAboutGameEntitys.at(0)->getComponent<AboutGameCom>();

        if(xAboutGameCom->mBackToMainMenu->isButtonPressed())
            JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
    }
}
