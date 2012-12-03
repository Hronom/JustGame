#ifndef MAINMENUWORLD_H
#define MAINMENUWORLD_H

#include <World.h>

class MainMenuWorld: public JGC::World
{
public:
    MainMenuWorld(QString xWorldName);
    ~MainMenuWorld();

    void load();
    void enter();
    void exit();
};

#endif
