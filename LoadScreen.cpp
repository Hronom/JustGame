#include "LoadScreen.h"

LoadScreen::LoadScreen(ICore *xCore)
{
	mCore = xCore;

	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("Loading.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

	mCurrentLayoutWidgets[0]->setVisible(false);

	mTextBox = mCore->getGui()->findWidget<MyGUI::TextBox>("LoadingText");
	mProgressBar = mCore->getGui()->findWidget<MyGUI::ProgressBar>("LoadingProgress");
}


LoadScreen::~LoadScreen()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void LoadScreen::show()
{
	MyGUI::PointerManager::getInstancePtr()->hide();
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void LoadScreen::hide()
{
	mCurrentLayoutWidgets[0]->setVisible(false);
	MyGUI::PointerManager::getInstancePtr()->show();
}

void LoadScreen::setProgress(int xProgressValue, std::string xText)
{
	mTextBox->setCaption(xText);
	mProgressBar->setProgressPosition(xProgressValue);
}
