#include <MainSystem.h>
#include <EntitySystem.h>

#include "creators/ComponentsCreators.h"
#include "systems/PlayerControl.h"
#include "systems/AIControl.h"
#include "systems/PhysGraphSync.h"
#include "systems/PlayerCameraSync.h"
#include "systems/Bullets.h"
#include "systems/DamageSys.h"
#include "systems/PlayerGUISys.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");



    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PhysBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "Weapon");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PlayerControllable");

    JGC::EntitySystem::instance()->addComponentToNode("AIControl", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("AIControl", "PhysBody");
    JGC::EntitySystem::instance()->addComponentToNode("AIControl", "Weapon");
    JGC::EntitySystem::instance()->addComponentToNode("AIControl", "AIControllable");

    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "CameraTrackable");

    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "Bullet");
    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("Bullets", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("DoDamage", "Bullet");
    JGC::EntitySystem::instance()->addComponentToNode("DoDamage", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("Damageable", "Health");
    JGC::EntitySystem::instance()->addComponentToNode("Damageable", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("PlayerStat", "Health");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerStat", "PlayerControllable");

    JGC::EntitySystem::instance()->addComponentToNode("EnemyStat", "Health");
    JGC::EntitySystem::instance()->addComponentToNode("EnemyStat", "AIControllable");
    JGC::EntitySystem::instance()->addComponentToNode("EnemyStat", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("GUI", "PlayerUI");



    GraphBody* xBackgroundGraphBody = JG::cBackgroundGraphBody("Background");
    JGC::EntitySystem::instance()->addComponent("Background", xBackgroundGraphBody);

    // Player
    {
        GraphBody* xGraphBody = JG::cPlayerGraphBody("PlayerGraphBody");
        JGC::EntitySystem::instance()->addComponent("Player", xGraphBody);

        PhysBody* xPhysBody = JG::cPlayerPhysBody();
        JGC::EntitySystem::instance()->addComponent("Player", xPhysBody);

        PlayerControllable* xPlayerControllable = JG::cPlayerControllable();
        JGC::EntitySystem::instance()->addComponent("Player", xPlayerControllable);

        CameraTrackable* xCameraTrackable = JG::cCameraTrackable("MainCamera");
        JGC::EntitySystem::instance()->addComponent("Player", xCameraTrackable);

        Weapon* xWeapon = JG::cWeapon(0.7f);
        JGC::EntitySystem::instance()->addComponent("Player", xWeapon);

        Health *xHealth = JG::cHealth(100,100);
        JGC::EntitySystem::instance()->addComponent("Player", xHealth);
    }

    // Enemy
    {
        AIControllable* xAIControllable = JG::cAIControllable();
        JGC::EntitySystem::instance()->addComponent("Enemy", xAIControllable);

        GraphBody* xGraphBody = JG::cEnemyGraphBody("EnemyGraphBody", Ogre::Vector3(13,13,0));
        JGC::EntitySystem::instance()->addComponent("Enemy", xGraphBody);

        PhysBody* xPhysBody = JG::cEnemyPhysBody(btVector3(13,13,0));
        JGC::EntitySystem::instance()->addComponent("Enemy", xPhysBody);

        Weapon* xWeapon = JG::cWeapon(1.01f);
        JGC::EntitySystem::instance()->addComponent("Enemy", xWeapon);

        Health *xHealth = JG::cHealth(100,100);
        JGC::EntitySystem::instance()->addComponent("Enemy", xHealth);
    }

    // GUI
    {
        PlayerUI *xPlayerUI = JG::cPlayerUI();
        JGC::EntitySystem::instance()->addComponent("GUI", xPlayerUI);
    }



    {
        PlayerControl *xPlayerControl;
        xPlayerControl = new PlayerControl();
        JGC::EntitySystem::instance()->addSystem(1, xPlayerControl);

        AIControl *xAIControl;
        xAIControl = new AIControl();
        JGC::EntitySystem::instance()->addSystem(2, xAIControl);

        PhysGraphSync *xPhysGraphSync;
        xPhysGraphSync = new PhysGraphSync();
        JGC::EntitySystem::instance()->addSystem(3, xPhysGraphSync);

        PlayerCameraSync *xPlayerCameraSync;
        xPlayerCameraSync = new PlayerCameraSync();
        JGC::EntitySystem::instance()->addSystem(4, xPlayerCameraSync);

        Bullets *xBullets;
        xBullets = new Bullets();
        JGC::EntitySystem::instance()->addSystem(5, xBullets);

        DamageSys *xDamageSys;
        xDamageSys = new DamageSys();
        JGC::EntitySystem::instance()->addSystem(6, xDamageSys);

        PlayerGUISys *xPlayerGUISys;
        xPlayerGUISys = new PlayerGUISys();
        JGC::EntitySystem::instance()->addSystem(7, xPlayerGUISys);
    }



    JGC::EntitySystem::instance()->printInfo();

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
