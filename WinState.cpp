#include "WinState.h"

WinState::WinState(ICore *xCore)
{
	mCore = xCore;

	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("WinMenu.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	MyGUI::Button *xButton;
	xButton = mCore->getGui()->findWidget<MyGUI::Button>("OkButton");
	xButton->eventMouseButtonClick += MyGUI::newDelegate(this, &WinState::buttonClicked);

	mCurrentLayoutWidgets[0]->setVisible(false);
}

WinState::~WinState()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void WinState::prepareState()
{

}

void WinState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void WinState::exit()
{
	mCurrentLayoutWidgets[0]->setVisible(false);
}

void WinState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown(); 
}

void WinState::buttonClicked(MyGUI::WidgetPtr xSender)
{
	mCore->needSwitchToStateId(0);
}
