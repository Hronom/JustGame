#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include <IState.h>
#include <ICore.h>

class MainMenuState: public IState
{
private:
	ICore *mCore;

	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	MainMenuState(ICore *xCore);
	~MainMenuState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void keyPressed(const OIS::KeyEvent& e);

private:
	void newGameClicked(MyGUI::Widget *xSender);
	void exitClicked(MyGUI::Widget *xSender);
};

#endif

