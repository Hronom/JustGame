#include "WinState.h"

WinState::WinState()
{
}

WinState::~WinState()
{
	exit();
}

void WinState::prepareState()
{
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("WinMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	MyGUI::Button *xButton;
	xButton = JGC::MainSystem::instance()->getGui()->findWidget<MyGUI::Button>("OkButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &WinState::okClicked);

	mCurrentLayoutWidgets[0]->setVisible(false);
}

void WinState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void WinState::exit()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void WinState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) JGC::MainSystem::instance()->needShutdown(); 
}

void WinState::okClicked(MyGUI::WidgetPtr xSender)
{
	JGC::MainSystem::instance()->needSwitchToState("MainMenuState");
}
