#ifndef PHYSBODYCOM_H
#define PHYSBODYCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <btBulletDynamicsCommon.h>

class PhysBodyCom: public JGC::IComponent
{
public:
    btCollisionShape *mCollisionShape;
    btRigidBody *mRigidBody;
};

Q_DECLARE_METATYPE(PhysBodyCom)

#endif
