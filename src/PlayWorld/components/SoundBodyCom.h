#ifndef SOUNDBODYCOM_H
#define SOUNDBODYCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <SoundSource.h>

class SoundBodyCom: public JGC::IComponent
{
public:
    JGC::SoundSource *mSoundSource;
};

Q_DECLARE_METATYPE(SoundBodyCom)

#endif
