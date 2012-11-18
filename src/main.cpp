#include <MainSystem.h>
#include <EntitySystem.h>

#include "creators/ComponentsCreators.h"
#include "systems/PlayerControl.h"
#include "systems/PhysGraphSync.h"
#include "systems/PlayerCameraSync.h"
#include "systems/Bullets.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");



    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PhysBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "Weapon");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PlayerControllable");

    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "CameraTrackable");

    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "Bullet");
    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "PhysBody");



    GraphBody* xBackgroundGraphBody = JG::cBackgroundGraphBody("Background");
    JGC::EntitySystem::instance()->addComponent("Background", xBackgroundGraphBody);

    {
        GraphBody* xGraphBody = JG::cPlayerGraphBody("PlayerGraphBody");
        JGC::EntitySystem::instance()->addComponent("Player", xGraphBody);

        PhysBody* xPhysBody = JG::cPlayerPhysBody();
        JGC::EntitySystem::instance()->addComponent("Player", xPhysBody);

        PlayerControllable* xPlayerControllable = JG::cPlayerControllable();
        JGC::EntitySystem::instance()->addComponent("Player", xPlayerControllable);

        CameraTrackable* xCameraTrackable = JG::cCameraTrackable("MainCamera");
        JGC::EntitySystem::instance()->addComponent("Player", xCameraTrackable);

        Weapon* xWeapon = JG::cWeapon(0.5f);
        JGC::EntitySystem::instance()->addComponent("Player", xWeapon);
    }
    {
        GraphBody* xGraphBody = JG::cEnemyGraphBody("EnemyGraphBody", Ogre::Vector3(13,13,0));
        JGC::EntitySystem::instance()->addComponent("Enemy", xGraphBody);

        PhysBody* xPhysBody = JG::cEnemyPhysBody(btVector3(13,13,0));
        JGC::EntitySystem::instance()->addComponent("Enemy", xPhysBody);

        Weapon* xWeapon = JG::cWeapon(3.0f);
        JGC::EntitySystem::instance()->addComponent("Enemy", xWeapon);
    }





    PlayerControl *xPlayerControl;
    xPlayerControl = new PlayerControl();
    JGC::EntitySystem::instance()->addSystem(1, xPlayerControl);

    PhysGraphSync *xPhysGraphSync;
    xPhysGraphSync = new PhysGraphSync();
    JGC::EntitySystem::instance()->addSystem(2, xPhysGraphSync);

    PlayerCameraSync *xPlayerCameraSync;
    xPlayerCameraSync = new PlayerCameraSync();
    JGC::EntitySystem::instance()->addSystem(3, xPlayerCameraSync);

    Bullets *xBullets;
    xBullets = new Bullets();
    JGC::EntitySystem::instance()->addSystem(4, xBullets);



    JGC::EntitySystem::instance()->printInfo();

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
