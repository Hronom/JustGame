#ifndef COMPONENTSCREATORS_H
#define COMPONENTSCREATORS_H

#include "../components/MainMenuCom.h"

#include "QString"

namespace JG
{
    // c prefix -> create
    // d prefix -> delete

    MainMenuCom* cMainMenuCom();
    void dMainMenuCom(MainMenuCom* xMainMenuCom);
}

#endif

