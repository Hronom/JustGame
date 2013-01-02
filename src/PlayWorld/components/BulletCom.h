#ifndef BULLETCOM_H
#define BULLETCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <Ogre.h>

class BulletCom: public JGC::IComponent
{
public:
    float mLiveTime;
    float mTotalLiveTime;

    qint32 mDamageCount;
};

Q_DECLARE_METATYPE(BulletCom)

#endif
