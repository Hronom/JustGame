#ifndef PLAYWORLD_H
#define PLAYWORLD_H

#include "components/GraphBodyCom.h"
#include "components/PhysBodyCom.h"
#include "components/CameraTrackableCom.h"
#include "components/HealthCom.h"
#include "components/PlayerControllableCom.h"
#include "components/AIControllableCom.h"
#include "components/WeaponCom.h"
#include "components/BulletCom.h"
#include "components/SoundBodyCom.h"
#include "components/PlayerUICom.h"

#include <World.h>
#include <QString>

#define BIT(x) (1<<(x))
enum CollisionGroups
{
    EMPTY_GROUP = 0,
    PLAYER_GROUP = BIT(0), //<Collide with PLAYER
    ENEMY_GROUP = BIT(1), //<Collide with ENEMY
    BulletCom_GROUP = BIT(2) //<Collide with BulletCom
};

class PlayWorld: public JGC::World
{
private:
    static unsigned int mEnemysCount;

public:
    PlayWorld(QString xWorldName);
    ~PlayWorld();

    void enter();
    void exit();

    ////////////////////////////////////////////////////////////
    // c prefix -> create
    // d prefix -> delete


    static GraphBodyCom* cBackgroundGraphBodyCom(QString xSceneManagerName, QString xComponentName);
    static GraphBodyCom* cPlayerGraphBodyCom(QString xSceneManagerName, QString xComponentName);
    static GraphBodyCom* cEnemyGraphBodyCom(QString xSceneManagerName, QString xComponentSuffix, Ogre::Vector3 xPosition);
    static GraphBodyCom* cBulletGraphBodyCom(QString xSceneManagerName, QString xComponentName, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination);
    static void dGraphBodyCom(QString xSceneManagerName, GraphBodyCom* xGraphBodyCom);



    static PhysBodyCom* cPlayerPhysBodyCom(QString xDynamicsWorldName);
    static PhysBodyCom* cEnemyPhysBodyCom(QString xDynamicsWorldName, btVector3 xPosition);
    static PhysBodyCom* cBulletPhysBodyCom(QString xDynamicsWorldName, short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    static void dPhysBodyCom(QString xDynamicsWorldName, PhysBodyCom* xPhysBodyCom);

    static SoundBodyCom* cWeaponComSoundBodyCom(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    static void dSoundBodyCom(SoundBodyCom* xSoundBodyCom);



    static CameraTrackableCom* cCameraTrackableCom(QString xSceneManagerName, QString xCameraName);
    static void dCameraTrackableCom(QString xSceneManagerName);



    static HealthCom* cHealthCom(qint32 xHealthComCurrent, qint32 xHealthComTotal);



    static PlayerControllableCom* cPlayerControllableCom();



    static AIControllableCom *cAIControllableCom();



    static WeaponCom* cWeaponCom(float xShootDelay);



    static BulletCom* cBulletCom(float xTotalLiveTime, qint32 xDamage);
    static void dBulletCom(BulletCom* xBulletCom);

    static PlayerUICom* cPlayerUICom();
    //void dPlayerUICom(PlayerUICom* xPlayerUICom);
};

#endif
