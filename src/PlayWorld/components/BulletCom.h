#ifndef BULLETCOM_H
#define BULLETCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <Ogre.h>

class BulletCom: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    qint32 mDamageCount;

    virtual qint32 getType() { return Components::BulletCom; }
};

#endif
