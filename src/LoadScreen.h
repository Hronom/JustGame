#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <MyGUI.h>

#include <MainSystem.h>
#include <ILoadScreen.h>

class LoadScreen: public JGC::ILoadScreen
{
private:
	MyGUI::Window *mWindow;
	MyGUI::TextBox *mTextBox;
	MyGUI::ProgressBar *mProgressBar;

public:
	LoadScreen();
	~LoadScreen();

	virtual void show();
	virtual void hide();

	virtual void setProgress(int xProgressValue, std::string xText);
};

#endif
