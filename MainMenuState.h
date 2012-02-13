#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include "iState.h"
#include "iCore.h"

class MainMenuState: public iState
{
private:
	iCore *mCore;

public:
	MainMenuState(iCore *xCore);
	~MainMenuState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void buttonClicked(MyGUI::WidgetPtr xSender);
};

#endif

