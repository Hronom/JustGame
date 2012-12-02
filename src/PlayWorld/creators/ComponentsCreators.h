#ifndef COMPONENTSCREATORS_H
#define COMPONENTSCREATORS_H

#include "../components/GraphBodyCom.h"
#include "../components/PhysBodyCom.h"
#include "../components/CameraTrackableCom.h"
#include "../components/HealthCom.h"
#include "../components/PlayerControllableCom.h"
#include "../components/AIControllableCom.h"
#include "../components/WeaponCom.h"
#include "../components/BulletCom.h"
#include "../components/SoundBodyCom.h"
#include "../components/PlayerUICom.h"

#include "QString"

#define BIT(x) (1<<(x))
enum CollisionGroups
{
    EMPTY_GROUP = 0,
    PLAYER_GROUP = BIT(0), //<Collide with PLAYER
    ENEMY_GROUP = BIT(1), //<Collide with ENEMY
    BulletCom_GROUP = BIT(2) //<Collide with BulletCom
};

namespace JG
{
    // c prefix -> create
    // d prefix -> delete

    static unsigned int mEnemysCount = 0;

    GraphBodyCom* cBackgroundGraphBodyCom(QString xSceneManagerName, QString xComponentName);
    GraphBodyCom* cPlayerGraphBodyCom(QString xSceneManagerName, QString xComponentName);
    GraphBodyCom* cEnemyGraphBodyCom(QString xSceneManagerName, QString xComponentSuffix, Ogre::Vector3 xPosition);
    GraphBodyCom* cBulletGraphBodyCom(QString xSceneManagerName, QString xComponentName, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination);
    void dGraphBodyCom(QString xSceneManagerName, GraphBodyCom* xGraphBodyCom);



    PhysBodyCom* cPlayerPhysBodyCom(QString xDynamicsWorldName);
    PhysBodyCom* cEnemyPhysBodyCom(QString xDynamicsWorldName, btVector3 xPosition);
    PhysBodyCom* cBulletPhysBodyCom(QString xDynamicsWorldName, short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    void dPhysBodyCom(QString xDynamicsWorldName, PhysBodyCom* xPhysBodyCom);

    SoundBodyCom* cWeaponComSoundBodyCom(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    void dSoundBodyCom(SoundBodyCom* xSoundBodyCom);



    CameraTrackableCom* cCameraTrackableCom(QString xSceneManagerName, QString xCameraName);
    void dCameraTrackableCom(QString xSceneManagerName);



    HealthCom* cHealthCom(qint32 xHealthComCurrent, qint32 xHealthComTotal);



    PlayerControllableCom* cPlayerControllableCom();



    AIControllableCom *cAIControllableCom();



    WeaponCom* cWeaponCom(float xShootDelay);



    BulletCom* cBulletCom(float xTotalLiveTime, qint32 xDamage);
    void dBulletCom(BulletCom* xBulletCom);

    PlayerUICom* cPlayerUICom();
    //void dPlayerUICom(PlayerUICom* xPlayerUICom);
}

#endif

