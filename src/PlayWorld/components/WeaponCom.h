#ifndef WEAPONCOM_H
#define WEAPONCOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class WeaponCom: public JGC::IComponent
{
public:
    float mShootDelay;
    float mTimeSinceLastShot;

    virtual qint32 getType() { return ComponentsTypes::WeaponCom; }
};

#endif
