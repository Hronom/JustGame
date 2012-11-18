#ifndef GRAPHBODY_H
#define GRAPHBODY_H

#include <Ogre.h>
#include "IComponent.h"

class GraphBody: public JGC::IComponent
{
public:
    Ogre::ManualObject *mManualObject;
    Ogre::Entity *mEntity;
    Ogre::SceneNode *mSceneNode;

    virtual QString getType() { return "GraphBody"; }
};

#endif
