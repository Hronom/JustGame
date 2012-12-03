#include <MainSystem.h>
#include <WorldsSystem.h>

#include "MainMenuWorld/MainMenuWorld.h"
#include "PlayWorld/PlayWorld.h"

#include <QDebug>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

    MainMenuWorld *xMainMenuWorld;
    xMainMenuWorld = new MainMenuWorld("MainMenuWorld");
    JGC::WorldsSystem::instance()->addWorld(xMainMenuWorld);
    JGC::WorldsSystem::instance()->loadWorld("MainMenuWorld");
    JGC::WorldsSystem::instance()->setActiveWorld("MainMenuWorld");

    PlayWorld *xPlayWorld;
    xPlayWorld = new PlayWorld("PlayWorld");
    JGC::WorldsSystem::instance()->addWorld(xPlayWorld);
    //JGC::WorldsSystem::instance()->loadWorld("PlayWorld");
    //JGC::WorldsSystem::instance()->setActiveWorld("PlayWorld");

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
