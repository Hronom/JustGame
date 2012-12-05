#ifndef SOUNDBODYCOM_H
#define SOUNDBODYCOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <SoundSource.h>

class SoundBodyCom: public JGC::IComponent
{
public:
    JGC::SoundSource *mSoundSource;

    virtual qint32 getType() { return ComponentsTypes::SoundBodyCom; }
};

#endif
