#ifndef WEAPONCOM_H
#define WEAPONCOM_H

#include <Ogre.h>
#include "IComponent.h"

class WeaponCom: public JGC::IComponent
{
public:
    float mShootDelay;
    float mTimeSinceLastShot;

    virtual QString getType() { return "Weapon"; }
};

#endif
