#ifndef LOSESTATE_H
#define LOSESTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include "iCore.h"
#include "iState.h"

class LoseState: public iState
{
private:
	iCore *mCore;

public:
	LoseState(iCore *xCore);
	~LoseState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void buttonClicked(MyGUI::WidgetPtr xSender);
};

#endif

