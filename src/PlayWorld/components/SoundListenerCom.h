#ifndef SOUNDLISTENERCOM_H
#define SOUNDLISTENERCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <SoundListener.h>

class SoundListenerCom: public JGC::IComponent
{
public:
    JGC::SoundListener *mSoundListener;
};

Q_DECLARE_METATYPE(SoundListenerCom)

#endif
