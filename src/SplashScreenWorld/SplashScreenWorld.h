#ifndef SPLASHSCREENWORLD_H
#define SPLASHSCREENWORLD_H

#include <World.h>

class SplashScreenWorld: public JGC::World
{
public:
    SplashScreenWorld(QString xWorldName);
    ~SplashScreenWorld();

    void enter();
    void exit();
};

#endif
