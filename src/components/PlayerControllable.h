#ifndef PLAYERCONTROLLABLE_H
#define PLAYERCONTROLLABLE_H

#include <Ogre.h>
#include "IComponent.h"

class PlayerControllable: public JGC::IComponent
{
public:
    virtual QString getType() { return "PlayerControllable"; }
};

#endif
