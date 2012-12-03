#ifndef MAINMENUCOM_H
#define MAINMENUCOM_H

#include <MyGUI.h>
#include "IComponent.h"

class MainMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mNewGameButton;
    MyGUI::Button *mExitButton;
    MyGUI::Button *mAboutProgram;

    virtual QString getType() { return "MainMenuCom"; }
};

#endif
