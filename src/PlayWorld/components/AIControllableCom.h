#ifndef AICONTROLLABLECOM_H
#define AICONTROLLABLECOM_H

#include <Ogre.h>
#include "IComponent.h"

class AIControllableCom: public JGC::IComponent
{
public:
    virtual QString getType() { return "AIControllableCom"; }
};

#endif
