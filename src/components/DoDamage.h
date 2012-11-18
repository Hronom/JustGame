#ifndef DODAMAGE_H
#define DODAMAGE_H

#include <Ogre.h>
#include "IComponent.h"

class DoDamage: public JGC::IComponent
{
public:
    qint32 mDamageCount;

    virtual QString getType() { return "DoDamage"; }
};

#endif
