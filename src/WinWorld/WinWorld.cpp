#include "WinWorld.h"

#include "systems/WinMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>

WinWorld::WinWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode(Nodes::WinMenuNode, Components::WinMenuCom);

    JGC::GraphicSystem::instance()->createSceneManager(this->getName());

    WinMenuSys *xWinMenuSys;
    xWinMenuSys = new WinMenuSys();
    this->addSystem(1, xWinMenuSys);
}

WinWorld::~WinWorld()
{
    WinMenuCom *xWinMenuCom;
    xWinMenuCom = static_cast<WinMenuCom*>(this->getEntity("WinMenuEntity")->getComponent(Components::WinMenuCom));
    dWinMenuCom(xWinMenuCom);
}

void WinWorld::load()
{
    this->setWorldLoaded(true);
}

void WinWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());

    WinMenuCom *xWinMenuCom = cWinMenuCom();
    this->addComponent("WinMenuEntity", xWinMenuCom);

    this->setWorldActive(true);
}

void WinWorld::exit()
{
    QVector<JGC::Entity*> xWinMenuEntitys;
    xWinMenuEntitys = this->getEntitysInNode(Nodes::WinMenuNode);

    WinMenuCom *xWinMenuCom;
    xWinMenuCom = static_cast<WinMenuCom*>(xWinMenuEntitys.at(0)->getComponent(Components::WinMenuCom));

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
