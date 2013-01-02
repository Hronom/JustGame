#ifndef CAMERATRACKABLECOM_H
#define CAMERATRACKABLECOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <Ogre.h>

class CameraTrackableCom: public JGC::IComponent
{
public:
    Ogre::Camera* mCamera;
};

Q_DECLARE_METATYPE(CameraTrackableCom)

#endif
