#ifndef MAINMENUSYS_H
#define MAINMENUSYS_H

#include "ISystem.h"

class MainMenuSys: public JGC::ISystem
{
public:
    MainMenuSys();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
