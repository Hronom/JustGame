#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "ISystem.h"
#include "Entity.h"

class PlayerControl: public JGC::ISystem
{
public:
    QString getNodeType() { return "PlayerControl"; }
    void proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate);
};

#endif
