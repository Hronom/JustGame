#include "LoseWorld.h"

#include "systems/LoseMenuSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>

LoseWorld::LoseWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<LoseMenuCom>(Nodes::LoseMenuNode);
}

LoseWorld::~LoseWorld()
{
    this->removeComponentFromNode<LoseMenuCom>(Nodes::LoseMenuNode);
}

void LoseWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    }

    {
        LoseMenuCom *xLoseMenuCom = cLoseMenuCom();
        this->addComponent("LoseMenuEntity", xLoseMenuCom);
    }

    {
        LoseMenuSys *xLoseMenuSys;
        xLoseMenuSys = new LoseMenuSys();
        this->addSystem(1, xLoseMenuSys);
    }

    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    this->setWorldActive(true);
}

void LoseWorld::exit()
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

            LoseMenuCom *xLoseMenuCom;
            xLoseMenuCom = xEntity->getComponent<LoseMenuCom>();
            if(xLoseMenuCom != NULL)
            {
                dLoseMenuCom(xLoseMenuCom);
                this->removeComponent(xEntity->getName(), xLoseMenuCom);
            }

            this->removeEntity(xEntity->getName());
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
    }

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
