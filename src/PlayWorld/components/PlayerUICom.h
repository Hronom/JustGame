#ifndef PLAYERUICOM_H
#define PLAYERUICOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <MyGUI.h>

class PlayerUICom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::ProgressBar *mPlayerHealthBar;
    MyGUI::Widget *mEnemyPanel;
    MyGUI::ProgressBar *mEnemyHealthBar;
};

Q_DECLARE_METATYPE(PlayerUICom)

#endif
