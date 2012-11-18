#ifndef COMPONENTSCREATORS_H
#define COMPONENTSCREATORS_H

#include "../components/GraphBody.h"
#include "../components/PhysBody.h"
#include "../components/CameraTrackable.h"
#include "../components/Health.h"
#include "../components/DoDamage.h"
#include "../components/PlayerControllable.h"
#include "../components/Weapon.h"

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

    static unsigned int mBulletsCount = 0;

    GraphBody* cPlayerGraphBody(QString xComponentName);
    GraphBody* cEnemyGraphBody(QString xComponentName);
    GraphBody* cBulletGraphBody(QString xComponentSuffix, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination);
    void dGraphBody(GraphBody* xGraphBody);



    PhysBody* cPlayerPhysBody();
    PhysBody* cEnemyPhysBody();
    PhysBody* cBulletPhysBody(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation);
    void dPhysBody(PhysBody* xPhysBody);



    CameraTrackable* cCameraTrackable(QString xCameraName);
    void dCameraTrackable();



    Health* cHealth(qint32 xHealthCurrent, qint32 xHealthTotal);



    DoDamage* cDoDamage(qint32 xDamageCount);



    PlayerControllable* cPlayerControllable();



    Weapon* cWeapon(float xShootDelay);
}

#endif

