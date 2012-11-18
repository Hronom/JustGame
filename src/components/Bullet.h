#ifndef BULLET_H
#define BULLET_H

#include <Ogre.h>
#include "IComponent.h"

class Bullet: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    virtual QString getType() { return "Bullet"; }
};

#endif
