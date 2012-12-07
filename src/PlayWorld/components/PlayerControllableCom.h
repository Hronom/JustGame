#ifndef PLAYERCONTROLLABLECOM_H
#define PLAYERCONTROLLABLECOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <Ogre.h>

class PlayerControllableCom: public JGC::IComponent
{
public:
    virtual qint32 getType() { return Components::PlayerControllableCom; }
};

#endif
