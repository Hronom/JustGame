#include "SplashScreenWorld.h"

#include "systems/SplashScreenSys.h"

#include <GraphicSystem.h>

SplashScreenWorld::SplashScreenWorld(QString xWorldName):World(xWorldName)
{
}

SplashScreenWorld::~SplashScreenWorld()
{
}

void SplashScreenWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
        JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    }

    {
        SplashScreenSys *xSplashScreenSys;
        xSplashScreenSys = new SplashScreenSys();
        this->addSystem(1, xSplashScreenSys);
    }

    this->setWorldActive(true);
}

void SplashScreenWorld::exit()
{
    // Delete systems
    {
        QList<JGC::ISystem*> xSystems;
        xSystems = this->getAllSystems();
        while(!xSystems.empty())
        {
            JGC::ISystem *xSystem;
            xSystem = xSystems.takeFirst();
            this->removeSystem(xSystem);
            delete xSystem;
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
    }

    this->setWorldActive(false);
}
