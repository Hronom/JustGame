#ifndef HEALTHCOM_H
#define HEALTHCOM_H

#include <Ogre.h>
#include "IComponent.h"

class HealthCom: public JGC::IComponent
{
public:
    qint32 mHealthTotal;
    qint32 mHealthCurrent;

    virtual QString getType() { return "Health"; }
};

#endif
