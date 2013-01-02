#ifndef MAINMENUWORLD_H
#define MAINMENUWORLD_H

#include "components/MainMenuCom.h"

#include <World.h>

class MainMenuWorld: public JGC::World
{
public:
    MainMenuWorld(QString xWorldName);
    ~MainMenuWorld();

    void enter();
    void exit();

    ////////////////////////////////////////////////////////////
    // c prefix -> create
    // d prefix -> delete

    static MainMenuCom* cMainMenuCom();
    static void dMainMenuCom(MainMenuCom* xMainMenuCom);
};

#endif
