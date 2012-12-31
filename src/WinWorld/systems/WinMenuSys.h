#ifndef WINMENUSYS_H
#define WINMENUSYS_H

#include "ISystem.h"

class WinMenuSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
