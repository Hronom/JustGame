#ifndef LOSEWORLD_H
#define LOSEWORLD_H

#include "components/LoseMenuCom.h"

#include <World.h>

class LoseWorld: public JGC::World
{
public:
    LoseWorld(QString xWorldName);
    ~LoseWorld();

    void enter();
    void exit();

    ////////////////////////////////////////////////////////////
    // c prefix -> create
    // d prefix -> delete

    static LoseMenuCom* cLoseMenuCom();
    static void dLoseMenuCom(LoseMenuCom *xLoseMenuCom);
};

#endif
