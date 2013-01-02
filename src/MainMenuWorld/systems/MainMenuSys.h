#ifndef MAINMENUSYS_H
#define MAINMENUSYS_H

#include "ISystem.h"
#include <QMetaType>

class MainMenuSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

Q_DECLARE_METATYPE(MainMenuSys)

#endif
