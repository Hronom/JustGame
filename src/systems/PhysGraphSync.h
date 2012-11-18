#ifndef PHYSGRAPHSYNC_H
#define PHYSGRAPHSYNC_H

#include "ISystem.h"

class PhysGraphSync: public JGC::ISystem
{
public:
    QString getNodeType() { return "PhysGraphSync"; }
    void proceedEntitys(QVector<JGC::Entity*> xEntitys, const float &xTimeSinceLastUpdate);
};

#endif
