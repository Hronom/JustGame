#ifndef MAINMENUCOM_H
#define MAINMENUCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <MyGUI.h>

class MainMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mNewGameButton;
    MyGUI::Button *mExitButton;
    MyGUI::Button *mAboutProgram;
};

Q_DECLARE_METATYPE(MainMenuCom)

#endif
