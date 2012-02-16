#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include "ICore.h"
#include "IState.h"

class SplashState: public IState
{
private:
	ICore *mCore;
	int mCurrentIndex;
	float mFadeSpeed;
	Ogre::Real mTimeToSwitch;
	Ogre::Real mCurrentTime;

	MyGUI::ImageBox *mOgreImage;
	MyGUI::ImageBox *mBulletImage;
	MyGUI::ImageBox *mHronoImage;

public:
	SplashState(ICore *xCore);
	~SplashState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual void keyPressed(const OIS::KeyEvent& e);
};

#endif

