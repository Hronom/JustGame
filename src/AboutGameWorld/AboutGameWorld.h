#ifndef ABOUTGAMEWORLD_H
#define ABOUTGAMEWORLD_H

#include "components/AboutGameCom.h"

#include <World.h>

class AboutGameWorld: public JGC::World
{
public:
    AboutGameWorld(QString xWorldName);
    ~AboutGameWorld();

    void enter();
    void exit();

    ////////////////////////////////////////////////////////////
    // c prefix -> create
    // d prefix -> delete

    static AboutGameCom* cAboutGameCom();
    static void dAboutGameCom(AboutGameCom* xAboutGameCom);
};

#endif
