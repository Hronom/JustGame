#ifndef PLAYERCAMERASYNC_H
#define PLAYERCAMERASYNC_H

#include <ISystem.h>

class PlayerCameraSync: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

#endif
