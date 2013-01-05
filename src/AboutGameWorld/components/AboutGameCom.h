#ifndef ABOUTGAMECOM_H
#define ABOUTGAMECOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <MyGUI.h>

class AboutGameCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mBackToMainMenu;
};

Q_DECLARE_METATYPE(AboutGameCom)

#endif
