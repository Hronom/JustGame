#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "ISystem.h"
#include "Entity.h"

class PlayerControl: public JGC::ISystem
{
private:
    unsigned int mBulletsEntityCounts;


public:
    PlayerControl(){mBulletsEntityCounts=0;}
    QString getNodeType() { return "PlayerControl"; }
    void proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate);
};

#endif
