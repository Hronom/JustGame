#ifndef PHYSBODYCOM_H
#define PHYSBODYCOM_H

#include <btBulletDynamicsCommon.h>
#include "IComponent.h"

class PhysBodyCom: public JGC::IComponent
{
public:
    btCollisionShape *mCollisionShape;
    btRigidBody *mRigidBody;

    virtual QString getType() { return "PhysBodyCom"; }
};

#endif
