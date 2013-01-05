#ifndef ABOUTGAMESYS_H
#define ABOUTGAMESYS_H

#include "ISystem.h"
#include <QMetaType>

class AboutGameSys: public JGC::ISystem
{
public:
    void injectUpdate(const float &xTimeSinceLastUpdate);
};

Q_DECLARE_METATYPE(AboutGameSys)

#endif
