#ifndef PLAYERUICOM_H
#define PLAYERUICOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <MyGUI.h>

class PlayerUICom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::ProgressBar *mPlayerHealthBar;
    MyGUI::Widget *mEnemyPanel;
    MyGUI::ProgressBar *mEnemyHealthBar;

    virtual qint32 getType() { return ComponentsTypes::PlayerUICom; }
};

#endif
