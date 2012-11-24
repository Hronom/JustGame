#ifndef PHYSGRAPHSYNC_H
#define PHYSGRAPHSYNC_H

#include "ISystem.h"

class PhysGraphSync: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
