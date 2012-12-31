#ifndef PLAYERWINLOSESYS_H
#define PLAYERWINLOSESYS_H

#include "ISystem.h"

class PlayerWinLoseSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
