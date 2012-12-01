#include "PlayWorld.h"

#include <GraphicSystem.h>

#include "creators/ComponentsCreators.h"
#include "systems/PlayerControl.h"
#include "systems/AIControl.h"
#include "systems/PhysGraphSync.h"
#include "systems/PlayerCameraSync.h"
#include "systems/Bullets.h"
#include "systems/DamageSys.h"
#include "systems/PlayerGUISys.h"

PlayWorld::PlayWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode("PlayerControl", "GraphBody");
    this->addComponentToNode("PlayerControl", "PhysBody");
    this->addComponentToNode("PlayerControl", "Weapon");
    this->addComponentToNode("PlayerControl", "PlayerControllable");

    this->addComponentToNode("AIControl", "GraphBody");
    this->addComponentToNode("AIControl", "PhysBody");
    this->addComponentToNode("AIControl", "Weapon");
    this->addComponentToNode("AIControl", "AIControllable");

    this->addComponentToNode("PhysGraphSync", "GraphBody");
    this->addComponentToNode("PhysGraphSync", "PhysBody");

    this->addComponentToNode("PlayerCameraSync", "GraphBody");
    this->addComponentToNode("PlayerCameraSync", "CameraTrackable");

    this->addComponentToNode("Bullets", "Bullet");
    this->addComponentToNode("Bullets", "GraphBody");
    this->addComponentToNode("Bullets", "PhysBody");

    this->addComponentToNode("DoDamage", "Bullet");
    this->addComponentToNode("DoDamage", "PhysBody");

    this->addComponentToNode("Damageable", "Health");
    this->addComponentToNode("Damageable", "PhysBody");

    this->addComponentToNode("PlayerStat", "Health");
    this->addComponentToNode("PlayerStat", "PlayerControllable");

    this->addComponentToNode("EnemyStat", "Health");
    this->addComponentToNode("EnemyStat", "AIControllable");
    this->addComponentToNode("EnemyStat", "PhysBody");

    this->addComponentToNode("GUI", "PlayerUI");
}

PlayWorld::~PlayWorld()
{

}

void PlayWorld::load()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
    }

    // Make entitys
    {
        GraphBody* xBackgroundGraphBody = JG::cBackgroundGraphBody("PlayWorld", "Background");
        this->addComponent("Background", xBackgroundGraphBody);

        // Player
        {
            GraphBody* xGraphBody = JG::cPlayerGraphBody("PlayWorld", "PlayerGraphBody");
            this->addComponent("Player", xGraphBody);

            PhysBody* xPhysBody = JG::cPlayerPhysBody();
            this->addComponent("Player", xPhysBody);

            PlayerControllable* xPlayerControllable = JG::cPlayerControllable();
            this->addComponent("Player", xPlayerControllable);

            CameraTrackable* xCameraTrackable = JG::cCameraTrackable("PlayWorld", "MainCamera");
            this->addComponent("Player", xCameraTrackable);

            Weapon* xWeapon = JG::cWeapon(0.3f);
            this->addComponent("Player", xWeapon);

            Health *xHealth = JG::cHealth(100,100);
            this->addComponent("Player", xHealth);
        }

        // Enemy
        {
            AIControllable* xAIControllable = JG::cAIControllable();
            this->addComponent("Enemy", xAIControllable);

            GraphBody* xGraphBody = JG::cEnemyGraphBody("PlayWorld", "EnemyGraphBody", Ogre::Vector3(13,13,0));
            this->addComponent("Enemy", xGraphBody);

            PhysBody* xPhysBody = JG::cEnemyPhysBody(btVector3(13,13,0));
            this->addComponent("Enemy", xPhysBody);

            Weapon* xWeapon = JG::cWeapon(1.01f);
            this->addComponent("Enemy", xWeapon);

            Health *xHealth = JG::cHealth(100,100);
            this->addComponent("Enemy", xHealth);
        }

        // GUI
        {
            PlayerUI *xPlayerUI = JG::cPlayerUI();
            this->addComponent("GUI", xPlayerUI);
        }
    }

    // Make systems
    {
        PlayerControl *xPlayerControl;
        xPlayerControl = new PlayerControl();
        this->addSystem(1, xPlayerControl);

        AIControl *xAIControl;
        xAIControl = new AIControl();
        this->addSystem(2, xAIControl);

        PhysGraphSync *xPhysGraphSync;
        xPhysGraphSync = new PhysGraphSync();
        this->addSystem(3, xPhysGraphSync);

        PlayerCameraSync *xPlayerCameraSync;
        xPlayerCameraSync = new PlayerCameraSync();
        this->addSystem(4, xPlayerCameraSync);

        Bullets *xBullets;
        xBullets = new Bullets();
        this->addSystem(5, xBullets);

        DamageSys *xDamageSys;
        xDamageSys = new DamageSys();
        this->addSystem(6, xDamageSys);

        PlayerGUISys *xPlayerGUISys;
        xPlayerGUISys = new PlayerGUISys();
        this->addSystem(7, xPlayerGUISys);
    }
}

void PlayWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
}

void PlayWorld::exit()
{

}
