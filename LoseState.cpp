#include "LoseState.h"

LoseState::LoseState(iCore *xCore)
{
	mCore = xCore;

	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("LoseMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	MyGUI::Button *xButton;
	xButton = mCore->getGui()->findWidget<MyGUI::Button>("OkButton2");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &LoseState::buttonClicked);

	mCurrentLayoutWidgets[0]->setVisible(false);
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

}

void LoseState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void LoseState::exit()
{
	mCurrentLayoutWidgets[0]->setVisible(false);
}

void LoseState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void LoseState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}

