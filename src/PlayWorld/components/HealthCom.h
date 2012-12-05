#ifndef HEALTHCOM_H
#define HEALTHCOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class HealthCom: public JGC::IComponent
{
public:
    qint32 mHealthTotal;
    qint32 mHealthCurrent;

    virtual qint32 getType() { return ComponentsTypes::HealthCom; }
};

#endif
