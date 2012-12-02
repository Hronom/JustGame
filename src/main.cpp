#include <MainSystem.h>
#include <WorldsSystem.h>

#include "PlayWorld/PlayWorld.h"

#include <QDebug>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

    PlayWorld *xPlayWorld;
    xPlayWorld = new PlayWorld("PlayWorld");

    JGC::WorldsSystem::instance()->addWorld(xPlayWorld);
    JGC::WorldsSystem::instance()->loadWorld("PlayWorld");
    while(!xPlayWorld->isWorldLoaded())
    {
        qDebug()<<"World isnt loaded";
    }
    JGC::WorldsSystem::instance()->setActiveWorld("PlayWorld");

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
