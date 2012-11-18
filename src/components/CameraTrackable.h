#ifndef CAMERATRACKABLE_H
#define CAMERATRACKABLE_H

#include <Ogre.h>
#include "IComponent.h"

class CameraTrackable: public JGC::IComponent
{
public:
    Ogre::Camera* mCamera;

    virtual QString getType() { return "CameraTrackable"; }
};

#endif
