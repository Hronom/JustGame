#include "SplashState.h"

SplashState::SplashState()
{
	mCurrentIndex = 0;
	mFadeSpeed = 1.5f;
	mTimeToSwitch = 3.0f;
	mCurrentTime = 0;
}


SplashState::~SplashState()
{
	exit();
}

void SplashState::prepareState()
{
	MyGUI::ImageBox *mImageBox;

	mImageBox = JGC::MainSystem::instance()->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default,"Main", "OgreLogo");
	mImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mImageBox->setImageTexture("OgreLogo.png");
	mImageBox->setAlpha(0);
	mCurrentLayoutWidgets.push_back(mImageBox);

	mImageBox = JGC::MainSystem::instance()->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "BulletLogo");
	mImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mImageBox->setImageTexture("BulletLogo.png");
	mImageBox->setAlpha(0);
	mCurrentLayoutWidgets.push_back(mImageBox);

	mImageBox = JGC::MainSystem::instance()->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "OpenALLogo");
	mImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mImageBox->setImageTexture("openalLogo.png");
	mImageBox->setAlpha(0);
	mCurrentLayoutWidgets.push_back(mImageBox);

	mImageBox = JGC::MainSystem::instance()->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "HronoLogo");
	mImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mImageBox->setImageTexture("HronoLogo.png");
	mImageBox->setAlpha(0);
	mCurrentLayoutWidgets.push_back(mImageBox);

	mImageBox = JGC::MainSystem::instance()->getGui()->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "GameLogo");
	mImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
	mImageBox->setImageTexture("JustGameLogo.png");
	mImageBox->setAlpha(0);
	mCurrentLayoutWidgets.push_back(mImageBox);

	mWidgetsIter = mCurrentLayoutWidgets.begin();

	mSoundNode1 = JGC::Sound::SoundSystem::instance()->createSoundSource(0.0f,0.0f,0.0f,"../Media/Sound/impulse.wav",false);
}

void SplashState::enter()
{
	MyGUI::PointerManager::getInstancePtr()->setVisible(false);
}

void SplashState::exit()
{
	mWidgetsIter = mCurrentLayoutWidgets.begin();
	while(mWidgetsIter != mCurrentLayoutWidgets.end())
	{
		MyGUI::Gui::getInstancePtr()->destroyWidget((*mWidgetsIter));
		++mWidgetsIter;
	}
	mCurrentLayoutWidgets.clear();

	MyGUI::PointerManager::getInstancePtr()->setVisible(true);
}

void SplashState::needUpdate(const Ogre::FrameEvent& evt)
{
	if(mWidgetsIter != mCurrentLayoutWidgets.end())
	{
		if(mCurrentIndex == 0)
		{
			if(evt.timeSinceLastFrame == 0) return;
			
			if((*mWidgetsIter)->getAlpha() == 0) mSoundNode1->play();

			float xValue = (*mWidgetsIter)->getAlpha() + mFadeSpeed * evt.timeSinceLastFrame;

			if(xValue < 1.0f)
				(*mWidgetsIter)->setAlpha(xValue);
			else
			{
				(*mWidgetsIter)->setAlpha(1.0f);
				mCurrentIndex++;
			}
		}

		if(mCurrentIndex == 1)
		{
			if(mCurrentTime <= mTimeToSwitch)
				mCurrentTime += evt.timeSinceLastFrame;
			else
			{
				mCurrentTime = 0;
				mCurrentIndex++;
			}
		}

		if(mCurrentIndex == 2)
		{
			float xValue = (*mWidgetsIter)->getAlpha() - mFadeSpeed * evt.timeSinceLastFrame;

			if(xValue > 0.0f)
				(*mWidgetsIter)->setAlpha(xValue);
			else
			{
				(*mWidgetsIter)->setAlpha(0.0f);
				mCurrentIndex++;
			}
		}

		if(mCurrentIndex == 3)
		{
			++mWidgetsIter;
			mCurrentIndex = 0;
		}
	}
	else
	{
		JGC::MainSystem::instance()->needSwitchToState("MainMenuState");
	}
}

void SplashState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	skipCurrentLogo();
}

void SplashState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_ESCAPE)
		JGC::MainSystem::instance()->needShutdown();
	else
		skipCurrentLogo();
}

void SplashState::skipCurrentLogo()
{
	(*mWidgetsIter)->setAlpha(0);
	mCurrentTime = 0;
	mCurrentIndex = 0;
	++mWidgetsIter;
}