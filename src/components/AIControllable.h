#ifndef AICONTROLLABLE_H
#define AICONTROLLABLE_H

#include <Ogre.h>
#include "IComponent.h"

class AIControllable: public JGC::IComponent
{
public:
    virtual QString getType() { return "AIControllable"; }
};

#endif
