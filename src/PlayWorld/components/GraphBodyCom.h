#ifndef GRAPHBODYCOM_H
#define GRAPHBODYCOM_H

#include "../../Library.h"

#include <IComponent.h>
#include <Ogre.h>

class GraphBodyCom: public JGC::IComponent
{
public:
    Ogre::ManualObject *mManualObject;
    Ogre::Entity *mEntity;
    Ogre::SceneNode *mSceneNode;

    virtual qint32 getType() { return Components::GraphBodyCom; }
};

#endif
