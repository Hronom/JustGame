#ifndef BULLETCOM_H
#define BULLETCOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class BulletCom: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    qint32 mDamageCount;

    virtual qint32 getType() { return ComponentsTypes::BulletCom; }
};

#endif
