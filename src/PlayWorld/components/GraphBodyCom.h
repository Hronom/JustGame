#ifndef GRAPHBODYCOM_H
#define GRAPHBODYCOM_H

#include <Ogre.h>
#include "IComponent.h"

class GraphBodyCom: public JGC::IComponent
{
public:
    Ogre::ManualObject *mManualObject;
    Ogre::Entity *mEntity;
    Ogre::SceneNode *mSceneNode;

    virtual QString getType() { return "GraphBody"; }
};

#endif
