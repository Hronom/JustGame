#include "WinWorld.h"

#include "systems/WinMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>

WinWorld::WinWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<WinMenuCom>(Nodes::WinMenuNode);
}

WinWorld::~WinWorld()
{
    this->removeComponentFromNode<WinMenuCom>(Nodes::WinMenuNode);
}

void WinWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    }

    {
        WinMenuCom *xWinMenuCom = cWinMenuCom();
        this->addComponent("WinMenuEntity", xWinMenuCom);
    }

    {
        WinMenuSys *xWinMenuSys;
        xWinMenuSys = new WinMenuSys();
        this->addSystem(1, xWinMenuSys);
    }

    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    this->setWorldActive(true);
}

void WinWorld::exit()
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

            WinMenuCom *xWinMenuCom;
            xWinMenuCom = xEntity->getComponent<WinMenuCom>();
            if(xWinMenuCom != NULL)
            {
                dWinMenuCom(xWinMenuCom);
                this->removeComponent(xEntity->getName(), xWinMenuCom);
            }

            this->removeEntity(xEntity->getName());
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
    }

    this->setWorldActive(false);
}

WinMenuCom* WinWorld::cWinMenuCom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("WinMenu.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

    MyGUI::Button *xButton;
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("OkButton");

    // Create component
    WinMenuCom *xWinMenuCom;
    xWinMenuCom = new WinMenuCom();
    xWinMenuCom->mLayoutWidgets = xCurrentLayoutWidgets;
    xWinMenuCom->mWinOkButton = xButton;

    return xWinMenuCom;
}

void WinWorld::dWinMenuCom(WinMenuCom *xWinMenuCom)
{
    if(xWinMenuCom->mLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xWinMenuCom->mLayoutWidgets);
        xWinMenuCom->mLayoutWidgets.clear();
    }
}
