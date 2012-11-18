#ifndef HEALTH_H
#define HEALTH_H

#include <Ogre.h>
#include "IComponent.h"

class Health: public JGC::IComponent
{
public:
    qint32 mHealthTotal;
    qint32 mHealthCurrent;

    virtual QString getType() { return "Health"; }
};

#endif
