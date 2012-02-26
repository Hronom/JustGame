#ifndef LOSESTATE_H
#define LOSESTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include <MainSystem.h>
#include <IState.h>

class LoseState: public JGC::States::IState
{
private:
	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

public:
	LoseState();
	~LoseState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();
	virtual void injectKeyPressed(const OIS::KeyEvent& e);
	
	void buttonClicked(MyGUI::WidgetPtr xSender);
};

#endif

