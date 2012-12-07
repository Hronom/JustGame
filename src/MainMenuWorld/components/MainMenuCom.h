#ifndef MAINMENUCOM_H
#define MAINMENUCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <MyGUI.h>

class MainMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mNewGameButton;
    MyGUI::Button *mExitButton;
    MyGUI::Button *mAboutProgram;

    virtual qint32 getType() { return Components::MainMenuCom; }
};

#endif
