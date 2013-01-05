#include "AboutGameWorld.h"

#include "systems/AboutGameSys.h"

#include <GraphicSystem.h>

AboutGameWorld::AboutGameWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<AboutGameCom>(Nodes::AboutGameNode);
}

AboutGameWorld::~AboutGameWorld()
{
    this->removeComponentFromNode<AboutGameCom>(Nodes::AboutGameNode);
}

void AboutGameWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    }

    {
        AboutGameCom *xAboutGameCom = cAboutGameCom();
        this->addComponent("AboutGameEntity", xAboutGameCom);
    }

    {
        AboutGameSys *xAboutGameSys;
        xAboutGameSys = new AboutGameSys();
        this->addSystem(1, xAboutGameSys);
    }

    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    this->setWorldActive(true);
}

void AboutGameWorld::exit()
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

            AboutGameCom *xAboutGameCom;
            xAboutGameCom = xEntity->getComponent<AboutGameCom>();
            if(xAboutGameCom != NULL)
            {
                dAboutGameCom(xAboutGameCom);
                this->removeComponent(xEntity->getName(), xAboutGameCom);
            }

            this->removeEntity(xEntity->getName());
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
    }

    this->setWorldActive(false);
}

AboutGameCom* AboutGameWorld::cAboutGameCom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("AboutProgram.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

    MyGUI::Button *xBackToMainMenu;
    xBackToMainMenu = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("BackToMainMenu");

    // Create component
    AboutGameCom *xAboutGameCom;
    xAboutGameCom = new AboutGameCom();
    xAboutGameCom->mLayoutWidgets = xCurrentLayoutWidgets;
    xAboutGameCom->mBackToMainMenu = xBackToMainMenu;

    return xAboutGameCom;
}

void AboutGameWorld::dAboutGameCom(AboutGameCom* xAboutGameCom)
{
    if(xAboutGameCom->mLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xAboutGameCom->mLayoutWidgets);
        xAboutGameCom->mLayoutWidgets.clear();
    }
}
