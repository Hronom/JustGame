#ifndef PLAYERUICOM_H
#define PLAYERUICOM_H

#include <MyGUI.h>
#include "IComponent.h"

class PlayerUICom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::ProgressBar *mPlayerHealthBar;
    MyGUI::Widget *mEnemyPanel;
    MyGUI::ProgressBar *mEnemyHealthBar;

    virtual QString getType() { return "PlayerUI"; }
};

#endif
