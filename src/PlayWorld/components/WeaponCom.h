#ifndef WEAPONCOM_H
#define WEAPONCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <Ogre.h>

class WeaponCom: public JGC::IComponent
{
public:
    float mShootDelay;
    float mTimeSinceLastShot;

    virtual qint32 getType() { return Components::WeaponCom; }
};

#endif
