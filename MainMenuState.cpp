#include "MainMenuState.h"

MainMenuState::MainMenuState(iCore *xCore)
{
	mCore = xCore;

	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("MainMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	MyGUI::Button *xButton;
	xButton = mCore->getGui()->findWidget<MyGUI::Button>("NewGameButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::buttonClicked);
	xButton = mCore->getGui()->findWidget<MyGUI::Button>("ExitButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &MainMenuState::buttonClicked);

	mCurrentLayoutWidgets[0]->setVisible(false);
}

MainMenuState::~MainMenuState()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void MainMenuState::prepareState()
{

}

void MainMenuState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void MainMenuState::exit()
{
	mCurrentLayoutWidgets[0]->setVisible(false);
}

void MainMenuState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void MainMenuState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	if(xSender->getUserString("ButtonType") == "NewGame")
	{
		mCore->needSwitchToStateId(1, true);
		return;
	}

	if(xSender->getUserString("ButtonType") == "Exit")
	{
		mCore->needShutdown();
		return;
	}
}
