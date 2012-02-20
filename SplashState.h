#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <MyGUI.h>
#include <OIS\OIS.h>

#include <ICore.h>
#include <IState.h>

#include <SoundNode.h>

class SplashState: public IState
{
private:
	ICore *mCore;
	int mCurrentIndex;
	float mFadeSpeed;
	Ogre::Real mTimeToSwitch;
	Ogre::Real mCurrentTime;

	std::vector<MyGUI::Widget*> mCurrentLayoutWidgets;
	std::vector<MyGUI::Widget*>::iterator mWidgetsIter;

	SoundNode *mSoundNode1;

public:
	SplashState(ICore *xCore);
	~SplashState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void keyPressed(const OIS::KeyEvent& e);

private:
	void skipCurrentLogo();
};

#endif

