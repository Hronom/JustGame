#ifndef HEALTHCOM_H
#define HEALTHCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <Ogre.h>

class HealthCom: public JGC::IComponent
{
public:
    qint32 mHealthTotal;
    qint32 mHealthCurrent;
};

Q_DECLARE_METATYPE(HealthCom)

#endif
