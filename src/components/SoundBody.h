#ifndef SOUNDBODY_H
#define SOUNDBODY_H

#include "IComponent.h"
#include <SoundSource.h>

class SoundBody: public JGC::IComponent
{
public:
    JGC::SoundSource *mSoundSource;

    virtual QString getType() { return "SoundBody"; }
};

#endif
