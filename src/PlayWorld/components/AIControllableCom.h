#ifndef AICONTROLLABLECOM_H
#define AICONTROLLABLECOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class AIControllableCom: public JGC::IComponent
{
public:
    virtual qint32 getType() { return ComponentsTypes::AIControllableCom; }
};

#endif
