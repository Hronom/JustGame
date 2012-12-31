#ifndef PLAYERDEATHSYS_H
#define PLAYERDEATHSYS_H

#include "ISystem.h"

class PlayerDeathSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
