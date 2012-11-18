#ifndef WEAPON_H
#define WEAPON_H

#include <Ogre.h>
#include "IComponent.h"

class Weapon: public JGC::IComponent
{
public:
    float mShootDelay;
    float mTimeSinceLastShot;

    virtual QString getType() { return "Weapon"; }
};

#endif
