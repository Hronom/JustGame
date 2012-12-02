#ifndef PLAYERCONTROLSYS_H
#define PLAYERCONTROLSYS_H

#include <ISystem.h>

class PlayerControlSys: public JGC::ISystem
{
public:
    PlayerControlSys();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
