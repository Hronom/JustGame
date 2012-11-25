#ifndef PLAYERGUISYS_H
#define PLAYERGUISYS_H

#include "ISystem.h"
#include "GraphicSystem.h"

class PlayerGUISys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
