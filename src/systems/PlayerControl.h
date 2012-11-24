#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include <ISystem.h>

class PlayerControl: public JGC::ISystem
{
public:
    PlayerControl();

    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
