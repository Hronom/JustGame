#ifndef PLAYERCONTROLLABLECOM_H
#define PLAYERCONTROLLABLECOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class PlayerControllableCom: public JGC::IComponent
{
public:
    virtual qint32 getType() { return ComponentsTypes::PlayerControllableCom; }
};

#endif
