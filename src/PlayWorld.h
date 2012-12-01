#ifndef PLAYWORLD_H
#define PLAYWORLD_H

#include <World.h>

class PlayWorld: public JGC::World
{
public:
    PlayWorld(QString xWorldName);
    ~PlayWorld();

    void load();
    void enter();
    void exit();
};

#endif
