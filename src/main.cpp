#include <MainSystem.h>
//#include <StatesSystem.h>
//#include "PlayGameState.h"
#include "EntitySystem.h"
#include "creators/ComponentsCreators.h"
#include "systems/PlayerControl.h"
#include "systems/PhysGraphSync.h"
#include "systems/PlayerCameraSync.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    JGC::MainSystem::initialize("Ogre.cfg","Plugins.cfg","../Media/Resources.cfg","Ogre.log", "MyGUI.log");

    /*LoadScreen *xLoadState = new LoadScreen();
	JGC::StatesSystem::instance()->setLoadState(xLoadState);

	SplashState *xSplashState = new SplashState();
	JGC::StatesSystem::instance()->addNormalState("SplashState", xSplashState);

	MainMenuState *xMainMenuState = new MainMenuState();
	JGC::StatesSystem::instance()->addNormalState("MainMenuState", xMainMenuState);

	PlayGameState *xPlayGameState = new PlayGameState();
	JGC::StatesSystem::instance()->addNormalState("PlayGameState", xPlayGameState);

	WinState *xWinState = new WinState();
	JGC::StatesSystem::instance()->addNormalState("WinState", xWinState);
	
	LoseState *xLoseState = new LoseState();
	JGC::StatesSystem::instance()->addNormalState("LoseState", xLoseState);

    JGC::StatesSystem::instance()->needSwitchToState("SplashState");*/

    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PhysBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "Weapon");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerControl", "PlayerControllable");

    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PhysGraphSync", "PhysBody");

    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "GraphBody");
    JGC::EntitySystem::instance()->addComponentToNode("PlayerCameraSync", "CameraTrackable");



    GraphBody* xGraphBody = JG::cPlayerGraphBody("PlayerGraphBody");
    JGC::EntitySystem::instance()->addComponent("Player", xGraphBody);

    PhysBody* xPhysBody = JG::cPlayerPhysBody();
    JGC::EntitySystem::instance()->addComponent("Player", xPhysBody);

    PlayerControllable* xPlayerControllable = JG::cPlayerControllable();
    JGC::EntitySystem::instance()->addComponent("Player", xPlayerControllable);

    CameraTrackable* xCameraTrackable = JG::cCameraTrackable("MainCamera");
    JGC::EntitySystem::instance()->addComponent("Player", xCameraTrackable);

    Weapon* xWeapon = JG::cWeapon(3);
    JGC::EntitySystem::instance()->addComponent("Player", xWeapon);




    PlayerControl *xPlayerControl;
    xPlayerControl = new PlayerControl();
    JGC::EntitySystem::instance()->addSystem(1, xPlayerControl);

    PhysGraphSync *xPhysGraphSync;
    xPhysGraphSync = new PhysGraphSync();
    JGC::EntitySystem::instance()->addSystem(2, xPhysGraphSync);

    PlayerCameraSync *xPlayerCameraSync;
    xPlayerCameraSync = new PlayerCameraSync();
    JGC::EntitySystem::instance()->addSystem(3, xPlayerCameraSync);



    JGC::EntitySystem::instance()->printInfo();

	JGC::MainSystem::instance()->run();
	JGC::MainSystem::shutdown();

	return 0;
}
