#ifndef CAMERATRACKABLECOM_H
#define CAMERATRACKABLECOM_H

#include "../../ComponentsTypes.h"

#include <IComponent.h>
#include <Ogre.h>

class CameraTrackableCom: public JGC::IComponent
{
public:
    Ogre::Camera* mCamera;

    virtual qint32 getType() { return ComponentsTypes::CameraTrackableCom; }
};

#endif
