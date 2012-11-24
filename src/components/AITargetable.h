#ifndef AITARGETABLE_H
#define AITARGETABLE_H

#include <Ogre.h>
#include "IComponent.h"

class AITargetable: public JGC::IComponent
{
public:

    virtual QString getType() { return "AITargetable"; }
};

#endif
