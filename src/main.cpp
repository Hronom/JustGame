#include <MainSystem.h>
#include <WorldsSystem.h>

#include "SplashScreenWorld/SplashScreenWorld.h"
#include "MainMenuWorld/MainMenuWorld.h"
#include "AboutGameWorld/AboutGameWorld.h"
#include "PlayWorld/PlayWorld.h"
#include "LoseWorld/LoseWorld.h"
#include "WinWorld/WinWorld.h"

#include <QDebug>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg", "Plugins.cfg", "../Media/Resources.cfg", "Ogre.log", "MyGUI.log");

    SplashScreenWorld *xSplashScreenWorld;
    xSplashScreenWorld = new SplashScreenWorld("SplashScreenWorld");
    JGC::WorldsSystem::instance()->addWorld(xSplashScreenWorld);

    MainMenuWorld *xMainMenuWorld;
    xMainMenuWorld = new MainMenuWorld("MainMenuWorld");
    JGC::WorldsSystem::instance()->addWorld(xMainMenuWorld);

    AboutGameWorld *xAboutGameWorld;
    xAboutGameWorld = new AboutGameWorld("AboutGameWorld");
    JGC::WorldsSystem::instance()->addWorld(xAboutGameWorld);

    PlayWorld *xPlayWorld;
    xPlayWorld = new PlayWorld("PlayWorld");
    JGC::WorldsSystem::instance()->addWorld(xPlayWorld);

    LoseWorld *xLoseWorld;
    xLoseWorld = new LoseWorld("LoseWorld");
    JGC::WorldsSystem::instance()->addWorld(xLoseWorld);

    WinWorld *xWinWorld;
    xWinWorld = new WinWorld("WinWorld");
    JGC::WorldsSystem::instance()->addWorld(xWinWorld);

    JGC::WorldsSystem::instance()->setActiveWorld("SplashScreenWorld");
    JGC::MainSystem::instance()->run();

    JGC::WorldsSystem::instance()->removeWorld("MainMenuWorld");
    delete xMainMenuWorld;
    JGC::WorldsSystem::instance()->removeWorld("AboutGameWorld");
    delete xAboutGameWorld;
    JGC::WorldsSystem::instance()->removeWorld("PlayWorld");
    delete xPlayWorld;
    JGC::WorldsSystem::instance()->removeWorld("LoseWorld");
    delete xLoseWorld;
    JGC::WorldsSystem::instance()->removeWorld("WinWorld");
    delete xWinWorld;

    JGC::MainSystem::shutdown();

    return 0;
}
