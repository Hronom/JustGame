#ifndef BULLET_H
#define BULLET_H

#include <Ogre.h>
#include "IComponent.h"

#include <qglobal.h>

class Bullet: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    qint32 mDamageCount;

    virtual QString getType() { return "Bullet"; }
};

#endif
