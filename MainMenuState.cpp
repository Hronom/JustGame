#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
	exit();
}

void MainMenuState::prepareState()
{
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("MainMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
	mCurrentLayoutWidgets[0]->setVisible(false);

	MyGUI::Button *xButton;
	xButton = JGC::MainSystem::instance()->getGui()->findWidget<MyGUI::Button>("NewGameButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::newGameClicked);
	xButton = JGC::MainSystem::instance()->getGui()->findWidget<MyGUI::Button>("ExitButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::exitClicked);	
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

void MainMenuState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) JGC::MainSystem::instance()->needShutdown(); 
}

void MainMenuState::newGameClicked(MyGUI::Widget *xSender)
{
	JGC::MainSystem::instance()->needSwitchToState("PlayGameState",true);
}

void MainMenuState::exitClicked(MyGUI::Widget *xSender)
{
	JGC::MainSystem::instance()->needShutdown();
}
