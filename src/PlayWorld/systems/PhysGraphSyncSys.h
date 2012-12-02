#ifndef PHYSGRAPHSYNCSYS_H
#define PHYSGRAPHSYNCSYS_H

#include "ISystem.h"

class PhysGraphSyncSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
