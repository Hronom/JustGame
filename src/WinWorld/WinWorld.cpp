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
    WinMenuCom *xWinMenuCom;
    xWinMenuCom = this->getEntity("WinMenuEntity")->getComponent<WinMenuCom>();
    dWinMenuCom(xWinMenuCom);
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
    QVector<JGC::Entity*> xWinMenuEntitys;
    xWinMenuEntitys = this->getEntitysInNode(Nodes::WinMenuNode);

    WinMenuCom *xWinMenuCom;
    xWinMenuCom = xWinMenuEntitys.at(0)->getComponent<WinMenuCom>();

    this->removeComponent("WinMenuEntity", xWinMenuCom);
    WinWorld::dWinMenuCom(xWinMenuCom);

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
