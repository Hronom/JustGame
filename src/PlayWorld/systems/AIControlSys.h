#ifndef AICONTROLSYS_H
#define AICONTROLSYS_H

#include "ISystem.h"

class AIControlSys: public JGC::ISystem
{
public:
    AIControlSys();
    ~AIControlSys();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
