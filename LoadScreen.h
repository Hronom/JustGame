#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <MyGUI.h>

#include <ICore.h>
#include <ILoadScreen.h>

class LoadScreen: public ILoadScreen
{
private:
	ICore *mCore;

	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

	MyGUI::Window *mWindow;
	MyGUI::TextBox *mTextBox;
	MyGUI::ProgressBar *mProgressBar;

public:
	LoadScreen(ICore *xCore);
	~LoadScreen();

	virtual void show();
	virtual void hide();

	virtual void setProgress(int xProgressValue, std::string xText);
};

#endif
