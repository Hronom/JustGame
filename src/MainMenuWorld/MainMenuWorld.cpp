#include "MainMenuWorld.h"

#include <GraphicSystem.h>

#include "creators/ComponentsCreators.h"
#include "systems/MainMenuSys.h"

MainMenuWorld::MainMenuWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode("MainMenu", "MainMenuCom");
}

MainMenuWorld::~MainMenuWorld()
{

}

void MainMenuWorld::load()
{
    JGC::GraphicSystem::instance()->createSceneManager(this->getName());

    MainMenuCom *xMainMenuCom = JG::cMainMenuCom();
    this->addComponent("MainMenuEntity", xMainMenuCom);

    MainMenuSys *xMainMenuSys;
    xMainMenuSys = new MainMenuSys();
    this->addSystem(1, xMainMenuSys);

    this->setWorldLoaded(true);
}

void MainMenuWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
}

void MainMenuWorld::exit()
{

}
