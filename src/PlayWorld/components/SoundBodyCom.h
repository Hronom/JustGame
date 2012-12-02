#ifndef SOUNDBODYCOM_H
#define SOUNDBODYCOM_H

#include "IComponent.h"
#include <SoundSource.h>

class SoundBodyCom: public JGC::IComponent
{
public:
    JGC::SoundSource *mSoundSource;

    virtual QString getType() { return "SoundBody"; }
};

#endif
