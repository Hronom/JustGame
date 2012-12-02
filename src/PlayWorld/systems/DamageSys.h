#ifndef DAMAGESYS_H
#define DAMAGESYS_H

#include "ISystem.h"

class DamageSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
