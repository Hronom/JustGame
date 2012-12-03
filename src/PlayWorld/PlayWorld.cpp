#include "PlayWorld.h"

#include <GraphicSystem.h>
#include <PhysicsSystem.h>

#include "creators/ComponentsCreators.h"
#include "systems/PlayerControlSys.h"
#include "systems/AIControlSys.h"
#include "systems/PhysGraphSyncSys.h"
#include "systems/PlayerCameraSyncSys.h"
#include "systems/BulletsSys.h"
#include "systems/DamageSys.h"
#include "systems/PlayerGUISys.h"

PlayWorld::PlayWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode("PlayerControl", "GraphBodyCom");
    this->addComponentToNode("PlayerControl", "PhysBodyCom");
    this->addComponentToNode("PlayerControl", "WeaponCom");
    this->addComponentToNode("PlayerControl", "PlayerControllableCom");

    this->addComponentToNode("AIControl", "GraphBodyCom");
    this->addComponentToNode("AIControl", "PhysBodyCom");
    this->addComponentToNode("AIControl", "WeaponCom");
    this->addComponentToNode("AIControl", "AIControllableCom");

    this->addComponentToNode("PhysGraphSync", "GraphBodyCom");
    this->addComponentToNode("PhysGraphSync", "PhysBodyCom");

    this->addComponentToNode("PlayerCameraSync", "GraphBodyCom");
    this->addComponentToNode("PlayerCameraSync", "CameraTrackableCom");

    this->addComponentToNode("Bullets", "BulletCom");
    this->addComponentToNode("Bullets", "GraphBodyCom");
    this->addComponentToNode("Bullets", "PhysBodyCom");

    this->addComponentToNode("DoDamage", "BulletCom");
    this->addComponentToNode("DoDamage", "PhysBodyCom");

    this->addComponentToNode("Damageable", "HealthCom");
    this->addComponentToNode("Damageable", "PhysBodyCom");

    this->addComponentToNode("PlayerStat", "HealthCom");
    this->addComponentToNode("PlayerStat", "PlayerControllableCom");

    this->addComponentToNode("EnemyStat", "HealthCom");
    this->addComponentToNode("EnemyStat", "AIControllableCom");
    this->addComponentToNode("EnemyStat", "PhysBodyCom");

    this->addComponentToNode("GameGUI", "PlayerUICom");
}

PlayWorld::~PlayWorld()
{

}

void PlayWorld::load()
{
    //JGC::GraphicSystem::instance()->pauseRender();
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
        JGC::PhysicsSystem::instance()->createDynamicsWorld(this->getName());
    }

    // Make entitys
    {
        GraphBodyCom* xBackgroundGraphBodyCom = JG::cBackgroundGraphBodyCom("PlayWorld", "Background");
        this->addComponent("Background", xBackgroundGraphBodyCom);

        // Player
        {
            GraphBodyCom* xGraphBodyCom = JG::cPlayerGraphBodyCom("PlayWorld", "PlayerGraphBody");
            this->addComponent("Player", xGraphBodyCom);

            PhysBodyCom* xPhysBodyCom = JG::cPlayerPhysBodyCom("PlayWorld");
            this->addComponent("Player", xPhysBodyCom);

            PlayerControllableCom* xPlayerControllableCom = JG::cPlayerControllableCom();
            this->addComponent("Player", xPlayerControllableCom);

            CameraTrackableCom* xCameraTrackableCom = JG::cCameraTrackableCom("PlayWorld", "MainCamera");
            this->addComponent("Player", xCameraTrackableCom);

            WeaponCom* xWeaponCom = JG::cWeaponCom(0.3f);
            this->addComponent("Player", xWeaponCom);

            HealthCom *xHealthCom = JG::cHealthCom(100,100);
            this->addComponent("Player", xHealthCom);
        }

        // Enemy
        {
            AIControllableCom* xAIControllableCom = JG::cAIControllableCom();
            this->addComponent("Enemy", xAIControllableCom);

            GraphBodyCom* xGraphBodyCom = JG::cEnemyGraphBodyCom("PlayWorld", "EnemyGraphBody", Ogre::Vector3(13,13,0));
            this->addComponent("Enemy", xGraphBodyCom);

            PhysBodyCom* xPhysBodyCom = JG::cEnemyPhysBodyCom("PlayWorld", btVector3(13,13,0));
            this->addComponent("Enemy", xPhysBodyCom);

            WeaponCom* xWeaponCom = JG::cWeaponCom(1.01f);
            this->addComponent("Enemy", xWeaponCom);

            HealthCom *xHealthCom = JG::cHealthCom(100,100);
            this->addComponent("Enemy", xHealthCom);
        }

        // GUI
        {
            PlayerUICom *xPlayerUICom = JG::cPlayerUICom();
            this->addComponent("GUI", xPlayerUICom);
        }

    }

    // Make systems
    {
        PlayerControlSys *xPlayerControlSys;
        xPlayerControlSys = new PlayerControlSys();
        this->addSystem(1, xPlayerControlSys);

        AIControlSys *xAIControlSys;
        xAIControlSys = new AIControlSys();
        this->addSystem(2, xAIControlSys);

        PhysGraphSyncSys *xPhysGraphSyncSys;
        xPhysGraphSyncSys = new PhysGraphSyncSys();
        this->addSystem(3, xPhysGraphSyncSys);

        PlayerCameraSyncSys *xPlayerCameraSyncSys;
        xPlayerCameraSyncSys = new PlayerCameraSyncSys();
        this->addSystem(4, xPlayerCameraSyncSys);

        BulletsSys *xBulletsSys;
        xBulletsSys = new BulletsSys();
        this->addSystem(5, xBulletsSys);

        DamageSys *xDamageSys;
        xDamageSys = new DamageSys();
        this->addSystem(6, xDamageSys);

        PlayerGUISys *xPlayerGUISys;
        xPlayerGUISys = new PlayerGUISys();
        this->addSystem(7, xPlayerGUISys);
    }

    //JGC::GraphicSystem::instance()->resumeRender();
    this->setWorldLoaded(true);
}

void PlayWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    JGC::PhysicsSystem::instance()->setActiveDynamicsWorld(this->getName());
}

void PlayWorld::exit()
{

}
