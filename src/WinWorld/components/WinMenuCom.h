#ifndef WINMENUCOM_H
#define WINMENUCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <MyGUI.h>

class WinMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mWinOkButton;

    virtual qint32 getType() { return Components::WinMenuCom; }
};

#endif
