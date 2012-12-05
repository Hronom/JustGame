#include "MainMenuWorld.h"

#include "systems/MainMenuSys.h"

#include <GraphicSystem.h>

MainMenuWorld::MainMenuWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode(Nodes::MainMenu, ComponentsTypes::MainMenuCom);
}

MainMenuWorld::~MainMenuWorld()
{

}

void MainMenuWorld::load()
{
    JGC::GraphicSystem::instance()->createSceneManager(this->getName());

    MainMenuCom *xMainMenuCom = cMainMenuCom();
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

MainMenuCom* MainMenuWorld::cMainMenuCom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("MainMenu.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
    //xCurrentLayoutWidgets[0]->setVisible(true);

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
