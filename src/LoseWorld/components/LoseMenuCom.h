#ifndef LOSEMENUCOM_H
#define LOSEMENUCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <MyGUI.h>

class LoseMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mLoseOkButton;
};

Q_DECLARE_METATYPE(LoseMenuCom)

#endif
