#ifndef HEALTHCOM_H
#define HEALTHCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <Ogre.h>

class HealthCom: public JGC::IComponent
{
public:
    qint32 mHealthTotal;
    qint32 mHealthCurrent;

    virtual qint32 getType() { return Components::HealthCom; }
};

#endif
