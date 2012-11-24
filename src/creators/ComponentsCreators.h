#ifndef COMPONENTSCREATORS_H
#define COMPONENTSCREATORS_H

#include "../components/GraphBody.h"
#include "../components/PhysBody.h"
#include "../components/CameraTrackable.h"
#include "../components/Health.h"
#include "../components/PlayerControllable.h"
#include "../components/AIControllable.h"
#include "../components/Weapon.h"
#include "../components/Bullet.h"
#include "../components/SoundBody.h"

#include "QString"

#define BIT(x) (1<<(x))
enum CollisionGroups
{
    EMPTY_GROUP = 0,
    PLAYER_GROUP = BIT(0), //<Collide with PLAYER
    ENEMY_GROUP = BIT(1), //<Collide with ENEMY
    BULLET_GROUP = BIT(2) //<Collide with BULLET
};

namespace JG
{
    // c prefix -> create
    // d prefix -> delete

    static unsigned int mEnemysCount = 0;

    GraphBody* cBackgroundGraphBody(QString xComponentName);
    GraphBody* cPlayerGraphBody(QString xComponentName);
    GraphBody* cEnemyGraphBody(QString xComponentSuffix, Ogre::Vector3 xPosition);
    GraphBody* cBulletGraphBody(QString xComponentName, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination);
    void dGraphBody(GraphBody* xGraphBody);



    PhysBody* cPlayerPhysBody();
    PhysBody* cEnemyPhysBody(btVector3 xPosition);
    PhysBody* cBulletPhysBody(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    void dPhysBody(PhysBody* xPhysBody);

    SoundBody* cWeaponSoundBody(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    void dSoundBody(SoundBody* xSoundBody);



    CameraTrackable* cCameraTrackable(QString xCameraName);
    void dCameraTrackable();



    Health* cHealth(qint32 xHealthCurrent, qint32 xHealthTotal);



    PlayerControllable* cPlayerControllable();



    AIControllable *cAIControllable();



    Weapon* cWeapon(float xShootDelay);



    Bullet* cBullet(float xTotalLiveTime, qint32 xDamage);
    void dBullet(Bullet* xBullet);
}

#endif

