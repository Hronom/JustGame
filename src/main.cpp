#include <MainSystem.h>
#include <WorldsSystem.h>

#include "MainMenuWorld/MainMenuWorld.h"
#include "PlayWorld/PlayWorld.h"
#include "LoseWorld/LoseWorld.h"
#include "WinWorld/WinWorld.h"

#include <QDebug>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

    MainMenuWorld *xMainMenuWorld;
    xMainMenuWorld = new MainMenuWorld("MainMenuWorld");
    JGC::WorldsSystem::instance()->addWorld(xMainMenuWorld);
    JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");

    PlayWorld *xPlayWorld;
    xPlayWorld = new PlayWorld("PlayWorld");
    JGC::WorldsSystem::instance()->addWorld(xPlayWorld);

    LoseWorld *xLoseWorld;
    xLoseWorld = new LoseWorld("LoseWorld");
    JGC::WorldsSystem::instance()->addWorld(xLoseWorld);

    WinWorld *xWinWorld;
    xWinWorld = new WinWorld("WinWorld");
    JGC::WorldsSystem::instance()->addWorld(xWinWorld);

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
