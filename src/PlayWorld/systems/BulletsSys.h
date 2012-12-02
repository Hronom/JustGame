#ifndef BULLETSSYS_H
#define BULLETSSYS_H

#include "ISystem.h"

class BulletsSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
