#ifndef PHYSBODYCOM_H
#define PHYSBODYCOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <btBulletDynamicsCommon.h>

class PhysBodyCom: public JGC::IComponent
{
public:
    btCollisionShape *mCollisionShape;
    btRigidBody *mRigidBody;

    virtual qint32 getType() { return ComponentsTypes::PhysBodyCom; }
};

#endif
