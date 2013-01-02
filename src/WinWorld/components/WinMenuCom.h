#ifndef WINMENUCOM_H
#define WINMENUCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <MyGUI.h>

class WinMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mWinOkButton;
};

Q_DECLARE_METATYPE(WinMenuCom)

#endif
