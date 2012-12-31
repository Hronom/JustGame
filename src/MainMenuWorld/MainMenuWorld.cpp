#include "MainMenuWorld.h"

#include "systems/MainMenuSys.h"

#include <GraphicSystem.h>

MainMenuWorld::MainMenuWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode(Nodes::MainMenuNode, Components::MainMenuCom);

    JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    MainMenuSys *xMainMenuSys;
    xMainMenuSys = new MainMenuSys();
    this->addSystem(1, xMainMenuSys);
}

MainMenuWorld::~MainMenuWorld()
{
    MainMenuCom *xMainMenuCom;
    xMainMenuCom = static_cast<MainMenuCom*>(this->getEntity("MainMenuEntity")->getComponent(Components::MainMenuCom));
    dMainMenuCom(xMainMenuCom);
}

void MainMenuWorld::load()
{
    MainMenuCom *xMainMenuCom = cMainMenuCom();
    this->addComponent("MainMenuEntity", xMainMenuCom);

    this->setWorldLoaded(true);
}

void MainMenuWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    this->setWorldActive(true);
}

void MainMenuWorld::exit()
{
    this->setWorldActive(false);
}

MainMenuCom* MainMenuWorld::cMainMenuCom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("MainMenu.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

    MyGUI::Button *xNewGameButton;
    xNewGameButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("NewGameButton");

    MyGUI::Button *xExitButton;
    xExitButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("ExitButton");

    MyGUI::Button *xAboutProgram;
    xAboutProgram = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("AboutProgram");

    // Create component
    MainMenuCom* xMainMenuCom;
    xMainMenuCom = new MainMenuCom();
    xMainMenuCom->mLayoutWidgets = xCurrentLayoutWidgets;
    xMainMenuCom->mNewGameButton = xNewGameButton;
    xMainMenuCom->mExitButton = xExitButton;
    xMainMenuCom->mAboutProgram = xAboutProgram;

    return xMainMenuCom;
}

void MainMenuWorld::dMainMenuCom(MainMenuCom* xMainMenuCom)
{
    if(xMainMenuCom->mLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xMainMenuCom->mLayoutWidgets);
        xMainMenuCom->mLayoutWidgets.clear();
    }
}
