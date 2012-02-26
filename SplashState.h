#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include <MainSystem.h>
#include <IState.h>

class SplashState: public JGC::States::IState
{
private:
	int mCurrentIndex;
	float mFadeSpeed;
	Ogre::Real mTimeToSwitch;
	Ogre::Real mCurrentTime;

	std::vector<MyGUI::Widget*> mCurrentLayoutWidgets;
	std::vector<MyGUI::Widget*>::iterator mWidgetsIter;

public:
	SplashState();
	~SplashState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual void injectUpdate(const float& xTimeSinceLastFrame);
	virtual void injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void injectKeyPressed(const OIS::KeyEvent& e);

private:
	void skipCurrentLogo();
};

#endif

