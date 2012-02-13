#ifndef WINSTATE_H
#define WINSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include "iCore.h"
#include "iState.h"

class WinState: public iState
{
private:
	iCore *mCore;

	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	WinState(iCore *xCore);
	~WinState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void keyPressed(const OIS::KeyEvent& e);
	
	void buttonClicked(MyGUI::WidgetPtr xSender);
};

#endif

