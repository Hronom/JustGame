#ifndef LOSEMENUCOM_H
#define LOSEMENUCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <MyGUI.h>

class LoseMenuCom: public JGC::IComponent
{
public:
    MyGUI::VectorWidgetPtr mLayoutWidgets;
    MyGUI::Button *mLoseOkButton;

    virtual qint32 getType() { return Components::LoseMenuCom; }
};

#endif
