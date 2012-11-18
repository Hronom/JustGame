#ifndef PLAYERCAMERASYNC_H
#define PLAYERCAMERASYNC_H

#include "ISystem.h"
#include "Entity.h"

class PlayerCameraSync: public JGC::ISystem
{
public:
    QString getNodeType() { return "PlayerCameraSync"; }
    void proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate);
};

#endif
