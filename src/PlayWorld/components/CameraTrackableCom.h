#ifndef CAMERATRACKABLECOM_H
#define CAMERATRACKABLECOM_H

#include <Ogre.h>
#include "IComponent.h"

class CameraTrackableCom: public JGC::IComponent
{
public:
    Ogre::Camera* mCamera;

    virtual QString getType() { return "CameraTrackableCom"; }
};

#endif
