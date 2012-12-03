#include "ComponentsCreators.h"

#include <GraphicSystem.h>

#include <QDebug>

namespace JG
{
    MainMenuCom* cMainMenuCom()
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

    void dMainMenuCom(MainMenuCom* xMainMenuCom)
    {
        if(xMainMenuCom->mLayoutWidgets.size() != 0)
        {
            MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xMainMenuCom->mLayoutWidgets);
            xMainMenuCom->mLayoutWidgets.clear();
        }
    }
}

