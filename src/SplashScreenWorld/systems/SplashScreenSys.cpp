#include "SplashScreenSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <MainSystem.h>
#include <InputSystem.h>

#include "../SplashScreenWorld.h"

#include "QDebug"

SplashScreenSys::SplashScreenSys()
{
    mMousePressed = false;

    mCurrentIndex = 0;
    mFadeSpeed = 1.5f;
    mTimeToSwitch = 3.0f;
    mCurrentTime = 0;

    MyGUI::ImageBox *xImageBox;
    MyGUI::Gui *xGUI = JGC::GraphicSystem::instance()->getGui();

    xImageBox = xGUI->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default,"Main", "OgreLogo");
    xImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
    xImageBox->setImageTexture("OgreLogo.png");
    xImageBox->setAlpha(0);
    mCurrentLayoutWidgets.push_back(xImageBox);

    xImageBox = xGUI->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "BulletLogo");
    xImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
    xImageBox->setImageTexture("BulletLogo.png");
    xImageBox->setAlpha(0);
    mCurrentLayoutWidgets.push_back(xImageBox);

    xImageBox = xGUI->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "OpenALLogo");
    xImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
    xImageBox->setImageTexture("openalLogo.png");
    xImageBox->setAlpha(0);
    mCurrentLayoutWidgets.push_back(xImageBox);

    xImageBox = xGUI->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "HronoLogo");
    xImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
    xImageBox->setImageTexture("HronoLogo.png");
    xImageBox->setAlpha(0);
    mCurrentLayoutWidgets.push_back(xImageBox);

    xImageBox = xGUI->createWidget<MyGUI::ImageBox>("ImageBox",0,0,0,0, MyGUI::Align::Default, "Main", "GameLogo");
    xImageBox->setRealCoord(0.0f,0.0f,1.0f,1.0f);
    xImageBox->setImageTexture("JustGameLogo.png");
    xImageBox->setAlpha(0);
    mCurrentLayoutWidgets.push_back(xImageBox);

    mWidgetsIter = mCurrentLayoutWidgets.begin();

    MyGUI::PointerManager::getInstancePtr()->setVisible(false);
}

SplashScreenSys::~SplashScreenSys()
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

void SplashScreenSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    if(JGC::InputSystem::instance()->isKeyDown(OIS::MB_Left))
    {
        if(mMousePressed == false)
        {
            mMousePressed = true;
            (*mWidgetsIter)->setAlpha(0);
            mCurrentTime = 0;
            mCurrentIndex = 0;
            ++mWidgetsIter;
        }
    }
    else
        mMousePressed = false;

    if(mWidgetsIter != mCurrentLayoutWidgets.end())
    {
        if(mCurrentIndex == 0)
        {
            if(xTimeSinceLastUpdate == 0) return;

            float xValue = (*mWidgetsIter)->getAlpha() + mFadeSpeed * xTimeSinceLastUpdate;

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
                mCurrentTime += xTimeSinceLastUpdate;
            else
            {
                mCurrentTime = 0;
                mCurrentIndex++;
            }
        }

        if(mCurrentIndex == 2)
        {
            float xValue = (*mWidgetsIter)->getAlpha() - mFadeSpeed * xTimeSinceLastUpdate;

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
        JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");
    }
}
