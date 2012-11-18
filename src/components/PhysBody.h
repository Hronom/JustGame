#ifndef PHYSBODY_H
#define PHYSBODY_H

#include <btBulletDynamicsCommon.h>
#include "IComponent.h"

class PhysBody: public JGC::IComponent
{
public:
    btCollisionShape *mCollisionShape;
    btRigidBody *mRigidBody;

    virtual QString getType() { return "PhysBody"; }
};

#endif
