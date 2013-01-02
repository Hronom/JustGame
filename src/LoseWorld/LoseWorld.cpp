#include "LoseWorld.h"

#include "systems/LoseMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>

LoseWorld::LoseWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<LoseMenuCom>(Nodes::LoseMenuNode);

    JGC::GraphicSystem::instance()->createSceneManager(this->getName());

    LoseMenuSys *xLoseMenuSys;
    xLoseMenuSys = new LoseMenuSys();
    this->addSystem(1, xLoseMenuSys);
}

LoseWorld::~LoseWorld()
{
    LoseMenuCom *xLoseMenuCom;
    xLoseMenuCom = this->getEntity("LoseMenuEntity")->getComponent<LoseMenuCom>();
    dLoseMenuCom(xLoseMenuCom);
}

void LoseWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());

    LoseMenuCom *xLoseMenuCom = cLoseMenuCom();
    this->addComponent("LoseMenuEntity", xLoseMenuCom);

    this->setWorldActive(true);
}

void LoseWorld::exit()
{
    QVector<JGC::Entity*> xLoseMenuEntitys;
    xLoseMenuEntitys = this->getEntitysInNode(Nodes::LoseMenuNode);

    LoseMenuCom *xLoseMenuCom;
    xLoseMenuCom = xLoseMenuEntitys.at(0)->getComponent<LoseMenuCom>();

    this->removeComponent("LoseMenuEntity", xLoseMenuCom);
    LoseWorld::dLoseMenuCom(xLoseMenuCom);

    this->setWorldActive(false);
}

LoseMenuCom* LoseWorld::cLoseMenuCom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("LoseMenu.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

    MyGUI::Button *xButton;
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("OkButton");

    // Create component
    LoseMenuCom *xLoseMenuCom;
    xLoseMenuCom = new LoseMenuCom();
    xLoseMenuCom->mLayoutWidgets = xCurrentLayoutWidgets;
    xLoseMenuCom->mLoseOkButton = xButton;

    return xLoseMenuCom;
}

void LoseWorld::dLoseMenuCom(LoseMenuCom *xLoseMenuCom)
{
    if(xLoseMenuCom->mLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xLoseMenuCom->mLayoutWidgets);
        xLoseMenuCom->mLayoutWidgets.clear();
    }
}
