#ifndef PLAYERCONTROLLABLECOM_H
#define PLAYERCONTROLLABLECOM_H

#include <Ogre.h>
#include "IComponent.h"

class PlayerControllableCom: public JGC::IComponent
{
public:
    virtual QString getType() { return "PlayerControllable"; }
};

#endif
