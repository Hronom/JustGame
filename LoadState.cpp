#include "LoadState.h"

LoadState::LoadState(iCore *xCore)
{
	mCore = xCore;

	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("Loading.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	mCurrentLayoutWidgets[0]->setVisible(false);

	mTextBox = mCore->getGui()->findWidget<MyGUI::TextBox>("LoadingText");
	mProgressBar = mCore->getGui()->findWidget<MyGUI::ProgressBar>("LoadingProgress");
}


LoadState::~LoadState()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void LoadState::show()
{
	MyGUI::PointerManager::getInstancePtr()->hide();
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void LoadState::hide()
{
	mCurrentLayoutWidgets[0]->setVisible(false);
	MyGUI::PointerManager::getInstancePtr()->show();
}

void LoadState::setProgress(int xProgressValue, std::string xText)
{
	mTextBox->setCaption(xText);
	mProgressBar->setProgressPosition(xProgressValue);
}
