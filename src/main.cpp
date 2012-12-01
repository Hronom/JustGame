#include <MainSystem.h>
#include <WorldsSystem.h>

#include "PlayWorld.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

    PlayWorld *xPlayWorld;
    xPlayWorld = new PlayWorld("PlayWorld");

    JGC::WorldsSystem::instance()->addWorld(xPlayWorld);
    JGC::WorldsSystem::instance()->loadWorld("PlayWorld");
    JGC::WorldsSystem::instance()->setActiveWorld("PlayWorld");

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
