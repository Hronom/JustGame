#ifndef AICONTROLABLE_H
#define AICONTROLABLE_H

#include <Ogre.h>
#include "IComponent.h"

class AIControlable: public JGC::IComponent
{
public:
    virtual QString getType() { return "AIControlable"; }
};

#endif
