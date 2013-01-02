#ifndef WEAPONCOM_H
#define WEAPONCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <Ogre.h>

class WeaponCom: public JGC::IComponent
{
public:
    float mShootDelay;
    float mTimeSinceLastShot;
};

Q_DECLARE_METATYPE(WeaponCom)

#endif
