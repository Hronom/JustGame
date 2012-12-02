#ifndef PLAYERCAMERASYNCSYS_H
#define PLAYERCAMERASYNCSYS_H

#include <ISystem.h>

class PlayerCameraSyncSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
