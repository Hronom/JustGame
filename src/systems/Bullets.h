#ifndef BULLETS_H
#define BULLETS_H

#include "ISystem.h"
#include "Entity.h"

class Bullets: public JGC::ISystem
{
public:
    QString getNodeType() { return "Bullets"; }
    void proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate);
};

#endif
