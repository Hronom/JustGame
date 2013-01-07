#include "PlayerCameraSyncSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <Entity.h>

#include "../components/GraphBodyCom.h"
#include "../components/CameraTrackableCom.h"

void PlayerCameraSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QList<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerCameraSyncNode);

    QList<JGC::Entity*>::Iterator xEntitysIter;
    xEntitysIter = xEntitys.begin();
    while(xEntitysIter != xEntitys.end())
    {
        JGC::Entity *xEntity;
        xEntity = (*xEntitysIter);

        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = xEntity->getComponent<GraphBodyCom>();

        CameraTrackableCom *xCameraTrackableCom;
        xCameraTrackableCom = xEntity->getComponent<CameraTrackableCom>();

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBodyCom->mSceneNode;

        Ogre::Vector3 xPlayerPos;
        xPlayerPos = xSceneNode->getPosition();

        Ogre::Vector3 xNewCameraPos;
        xNewCameraPos = xCameraTrackableCom->mCamera->getPosition();
        xNewCameraPos.x = xPlayerPos.x;
        xNewCameraPos.y = xPlayerPos.y;

        xCameraTrackableCom->mCamera->setPosition(xNewCameraPos);

        ++xEntitysIter;
    }
}
