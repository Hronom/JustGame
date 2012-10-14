#include "LoadScreen.h"

LoadScreen::LoadScreen()
{
	mWindow = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::Window>("Window", 65, 175, 510, 100, MyGUI::Align::Center, "Overlapped");

	mTextBox = mWindow->createWidget<MyGUI::TextBox>("TextBox", 5, 5, 490, 25, MyGUI::Align::Center);
	mProgressBar = mWindow->createWidget<MyGUI::ProgressBar>("ProgressBarFill", 5, 35, 490, 25, MyGUI::Align::Center);
	mProgressBar->setProgressRange(100);

	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
	mWindow->setVisible(false);
}


LoadScreen::~LoadScreen()
{
	MyGUI::WidgetManager::getInstancePtr()->destroyWidget(mProgressBar);
	MyGUI::WidgetManager::getInstancePtr()->destroyWidget(mTextBox);
	MyGUI::WidgetManager::getInstancePtr()->destroyWidget(mWindow);
}

void LoadScreen::show()
{
	MyGUI::PointerManager::getInstancePtr()->setVisible(false);
	mWindow->setVisible(true);
}

void LoadScreen::hide()
{
	mWindow->setVisible(false);
	MyGUI::PointerManager::getInstancePtr()->setVisible(true);
}

void LoadScreen::setProgress(int xProgressValue, std::string xText)
{
	mTextBox->setCaption(xText);
	mProgressBar->setProgressPosition(xProgressValue);
}
