#ifndef WINSTATE_H
#define WINSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include <MainSystem.h>
#include <IState.h>

class WinState: public JGC::IState
{
private:
	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	WinState();
	~WinState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual	void injectKeyPressed(const OIS::KeyEvent& e);

private:
	void okClicked(MyGUI::WidgetPtr xSender);
};

#endif

