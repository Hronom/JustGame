#ifndef BULLETS_H
#define BULLETS_H

#include "ISystem.h"

class Bullets: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
