#ifndef SPLASHSCREENSYS_H
#define SPLASHSCREENSYS_H

#include "ISystem.h"
#include <QMetaType>
#include <Ogre.h>
#include <MyGUI.h>

class SplashScreenSys: public JGC::ISystem
{
private:
    bool mMousePressed;

    int mCurrentIndex;
    float mFadeSpeed;
    Ogre::Real mTimeToSwitch;
    Ogre::Real mCurrentTime;

    std::vector<MyGUI::Widget*> mCurrentLayoutWidgets;
    std::vector<MyGUI::Widget*>::iterator mWidgetsIter;

public:
    SplashScreenSys();
    ~SplashScreenSys();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

Q_DECLARE_METATYPE(SplashScreenSys)

#endif
