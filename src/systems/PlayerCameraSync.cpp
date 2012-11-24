#include "PlayerCameraSync.h"

#include <GraphicSystem.h>
#include <EntitySystem.h>
#include <Entity.h>

#include "../components/GraphBody.h"
#include "../components/CameraTrackable.h"

void PlayerCameraSync::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::EntitySystem::instance()->getEntitysInNode("PlayerCameraSync");

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        GraphBody *xGraphBody;
        xGraphBody = static_cast<GraphBody*>(xEntitys.at(i)->getComponent("GraphBody"));

        CameraTrackable *xCameraTrackable;
        xCameraTrackable = static_cast<CameraTrackable*>(xEntitys.at(i)->getComponent("CameraTrackable"));

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBody->mSceneNode;

        Ogre::Vector3 xPlayerPos;
        xPlayerPos = xSceneNode->getPosition();

        Ogre::Vector3 xNewCameraPos;
        xNewCameraPos = xCameraTrackable->mCamera->getPosition();
        xNewCameraPos.x = xPlayerPos.x;
        xNewCameraPos.y = xPlayerPos.y;

        xCameraTrackable->mCamera->setPosition(xNewCameraPos);
    }
}
