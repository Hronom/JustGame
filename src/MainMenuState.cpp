#include "MainMenuState.h"
#include <GraphicSystem.h>
#include <StatesSystem.h>

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
    exit();
}

void MainMenuState::prepareState()
{
    prepareMainMenu();
}

void MainMenuState::enter()
{
    mCurrentLayoutWidgets[0]->setVisible(true);
}

void MainMenuState::exit()
{
    if(mCurrentLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
        mCurrentLayoutWidgets.clear();
    }
}

void MainMenuState::injectKeyPressed(const OIS::KeyEvent& e)
{
    if(e.key == OIS::KC_ESCAPE) JGC::MainSystem::instance()->needShutdown();
}

void MainMenuState::prepareMainMenu()
{
    mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("MainMenu.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
    mCurrentLayoutWidgets[0]->setVisible(false);

    MyGUI::Button *xButton;
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("NewGameButton");
    xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::newGameClicked);
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("AboutProgram");
    xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::aboutProgramClicked);
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("ExitButton");
    xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::exitClicked);
}

void MainMenuState::prepareAboutProgram()
{
    mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("AboutProgram.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
    mCurrentLayoutWidgets[0]->setVisible(false);

    MyGUI::Button *xButton;
    xButton = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Button>("BackToMainMenu");
    xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::backToMainMenuClicked);
}

void MainMenuState::newGameClicked(MyGUI::Widget *xSender)
{
    JGC::StatesSystem::instance()->needSwitchToState("PlayGameState",true);
}

void MainMenuState::aboutProgramClicked(MyGUI::Widget *xSender)
{
    if(mCurrentLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
        mCurrentLayoutWidgets.clear();
    }

    prepareAboutProgram();

    mCurrentLayoutWidgets[0]->setVisible(true);
}

void MainMenuState::exitClicked(MyGUI::Widget *xSender)
{
    JGC::MainSystem::instance()->needShutdown();
}

void MainMenuState::backToMainMenuClicked(MyGUI::Widget *xSender)
{
    if(mCurrentLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
        mCurrentLayoutWidgets.clear();
    }

    prepareMainMenu();

    mCurrentLayoutWidgets[0]->setVisible(true);
}
