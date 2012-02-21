#include "LoseState.h"

LoseState::LoseState()
{
}

LoseState::~LoseState()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void LoseState::prepareState()
{
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("LoseMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	MyGUI::Button *xButton;
	xButton = JGC::MainSystem::instance()->getGui()->findWidget<MyGUI::Button>("OkButton2");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoseState::buttonClicked);

	mCurrentLayoutWidgets[0]->setVisible(false);
}

void LoseState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void LoseState::exit()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void LoseState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) JGC::MainSystem::instance()->needShutdown(); 
}

void LoseState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	JGC::MainSystem::instance()->needSwitchToState("MainMenuState");
}

