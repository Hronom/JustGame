#include "MainMenuWorld.h"

#include "systems/MainMenuSys.h"

#include <GraphicSystem.h>

MainMenuWorld::MainMenuWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<MainMenuCom>(Nodes::MainMenuNode);
}

MainMenuWorld::~MainMenuWorld()
{
    this->removeComponentFromNode<MainMenuCom>(Nodes::MainMenuNode);
}

void MainMenuWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    }

    {
        MainMenuCom *xMainMenuCom = cMainMenuCom();
        this->addComponent("MainMenuEntity", xMainMenuCom);
    }

    {
        MainMenuSys *xMainMenuSys;
        xMainMenuSys = new MainMenuSys();
        this->addSystem(1, xMainMenuSys);
    }

    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    this->setWorldActive(true);
}

void MainMenuWorld::exit()
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

    // Delete entitys
    {
        QList<JGC::Entity*> xEntitys;
        xEntitys = this->getAllEntitys();
        while(!xEntitys.empty())
        {
            JGC::Entity *xEntity;
            xEntity = xEntitys.takeFirst();

            MainMenuCom *xMainMenuCom;
            xMainMenuCom = xEntity->getComponent<MainMenuCom>();
            if(xMainMenuCom != NULL)
            {
                dMainMenuCom(xMainMenuCom);
                this->removeComponent(xEntity->getName(), xMainMenuCom);
            }

            this->removeEntity(xEntity->getName());
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
    }

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
