#ifndef WINSTATE_H
#define WINSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include <ICore.h>
#include <IState.h>

class WinState: public IState
{
private:
	ICore *mCore;

	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	WinState(ICore *xCore);
	~WinState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void keyPressed(const OIS::KeyEvent& e);

private:
	void okClicked(MyGUI::WidgetPtr xSender);
};

#endif

