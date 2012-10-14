#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include <MainSystem.h>
#include <IState.h>

class MainMenuState: public JGC::IState
{
private:
	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	MainMenuState();
	~MainMenuState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void injectKeyPressed(const OIS::KeyEvent& e);

private:
    void prepareMainMenu();
    void prepareAboutProgram();
	void newGameClicked(MyGUI::Widget *xSender);
    void aboutProgramClicked(MyGUI::Widget *xSender);
	void exitClicked(MyGUI::Widget *xSender);
    void backToMainMenuClicked(MyGUI::Widget *xSender);
};

#endif

