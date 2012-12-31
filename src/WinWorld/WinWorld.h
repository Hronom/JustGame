#ifndef WINWORLD_H
#define WINWORLD_H

#include "components/WinMenuCom.h"

#include <World.h>

class WinWorld: public JGC::World
{
public:
    WinWorld(QString xWorldName);
    ~WinWorld();

    void load();
    void enter();
    void exit();

    ////////////////////////////////////////////////////////////
    // c prefix -> create
    // d prefix -> delete

    static WinMenuCom* cWinMenuCom();
    static void dWinMenuCom(WinMenuCom *xWinMenuCom);
};

#endif
