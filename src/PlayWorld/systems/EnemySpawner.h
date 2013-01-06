#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "ISystem.h"

class EnemySpawner: public JGC::ISystem
{
private:
    bool buttonDawn;

public:
    EnemySpawner();
    ~EnemySpawner();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
