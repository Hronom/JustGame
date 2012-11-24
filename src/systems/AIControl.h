#ifndef AICONTROL_H
#define AICONTROL_H

#include "ISystem.h"

class AIControl: public JGC::ISystem
{
public:
    AIControl();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
