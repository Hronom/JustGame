#ifndef BULLETCOM_H
#define BULLETCOM_H

#include <Ogre.h>
#include "IComponent.h"

#include <qglobal.h>

class BulletCom: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    qint32 mDamageCount;

    virtual QString getType() { return "Bullet"; }
};

#endif
