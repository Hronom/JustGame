#include "SplashState.h"

SplashState::SplashState(ICore *xCore)
{
	mCore = xCore;
	mCurrentIndex = 0;
	mFadeSpeed = 1.5f;
	mTimeToSwitch = 3.0f;
	mCurrentTime = 0;

	mOgreImage = mCore->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default,"Main", "OgreLogo");
	mOgreImage->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mOgreImage->setImageTexture("OgreLogo.png");
	mOgreImage->setAlpha(0);

	mBulletImage = mCore->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "BulletLogo");
	mBulletImage->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mBulletImage->setImageTexture("BulletLogo.png");
	mBulletImage->setAlpha(0);

	//mHronoImage = mCore->getGui()->createWidget<MyGUI::ImageBox>("ImageBox", 0,0,100,100,MyGUI::Align::Default, "Main", "HronoLogo");
}


SplashState::~SplashState()
{
	MyGUI::Gui::getInstancePtr()->destroyWidget(mOgreImage);
	MyGUI::Gui::getInstancePtr()->destroyWidget(mBulletImage);
	//MyGUI::Gui::getInstancePtr()->destroyWidget(mHronoImage);
}

void SplashState::prepareState()
{

}

void SplashState::enter()
{
	MyGUI::PointerManager::getInstancePtr()->hide();
}

void SplashState::exit()
{
	MyGUI::PointerManager::getInstancePtr()->show();
}

void SplashState::needUpdate(const Ogre::FrameEvent& evt)
{
	if(mCurrentIndex == 0)
	{
		if(evt.timeSinceLastFrame == 0) return;

		float xValue = mOgreImage->getAlpha() + mFadeSpeed * evt.timeSinceLastFrame;
		
		if(xValue < 1.0f)
			mOgreImage->setAlpha(xValue);
		else
		{
			mOgreImage->setAlpha(1.0f);
			mCurrentIndex++;
			mCurrentTime = 0;
		}
	}

	if(mCurrentIndex == 1)
	{
		if(mCurrentTime <= mTimeToSwitch)
			mCurrentTime += evt.timeSinceLastFrame;
		else
			mCurrentIndex++;
	}

	if(mCurrentIndex == 2)
	{
		float xValue = mOgreImage->getAlpha() - mFadeSpeed * evt.timeSinceLastFrame;
		
		if(xValue > 0.0f)
			mOgreImage->setAlpha(xValue);
		else
		{
			mOgreImage->setAlpha(0.0f);
			mCurrentIndex++;
		}
	}

	if(mCurrentIndex == 3)
	{
		if(evt.timeSinceLastFrame == 0) return;

		float xValue = mBulletImage->getAlpha() + mFadeSpeed * evt.timeSinceLastFrame;
		
		if(xValue < 1.0f)
			mBulletImage->setAlpha(xValue);
		else
		{
			mBulletImage->setAlpha(1.0f);
			mCurrentIndex++;
			mCurrentTime = 0;
		}
	}

	if(mCurrentIndex == 4)
	{
		if(mCurrentTime <= mTimeToSwitch)
			mCurrentTime += evt.timeSinceLastFrame;
		else
			mCurrentIndex++;
	}

	if(mCurrentIndex == 5)
	{
		float xValue = mBulletImage->getAlpha() - mFadeSpeed * evt.timeSinceLastFrame;
		
		if(xValue > 0.0f)
			mBulletImage->setAlpha(xValue);
		else
		{
			mBulletImage->setAlpha(0.0f);
			mCurrentIndex++;
		}
	}

	if(mCurrentIndex == 6)
	{
		mOgreImage->setVisible(false);
		mBulletImage->setVisible(false);
		mCore->needSwitchToStateId(0);
	}
}

void SplashState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown();
}