#ifndef GRAPHBODYCOM_H
#define GRAPHBODYCOM_H

#include "../../Nodes.h"

#include <IComponent.h>
#include <Ogre.h>

class GraphBodyCom: public JGC::IComponent
{
public:
    Ogre::ManualObject *mManualObject;
    Ogre::Entity *mEntity;
    Ogre::SceneNode *mSceneNode;
};

Q_DECLARE_METATYPE(GraphBodyCom)

#endif
