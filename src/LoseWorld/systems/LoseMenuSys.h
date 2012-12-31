#ifndef LOSEMENUSYS_H
#define LOSEMENUSYS_H

#include "ISystem.h"

class LoseMenuSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
