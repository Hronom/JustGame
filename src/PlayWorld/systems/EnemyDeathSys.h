#ifndef ENEMYDEATHSYS_H
#define ENEMYDEATHSYS_H

#include "ISystem.h"

class EnemyDeathSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
