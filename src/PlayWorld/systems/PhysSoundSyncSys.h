#ifndef PHYSSOUNDSYNCSYS_H
#define PHYSSOUNDSYNCSYS_H

#include "ISystem.h"

class PhysSoundSyncSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
