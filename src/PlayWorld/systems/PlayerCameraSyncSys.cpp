#include "PlayerCameraSyncSys.h"

#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <Entity.h>

#include "../components/GraphBodyCom.h"
#include "../components/CameraTrackableCom.h"

void PlayerCameraSyncSys::injectUpdate(const float &xTimeSinceLastUpdate)
{
    QVector<JGC::Entity*> xEntitys;
    xEntitys = JGC::WorldsSystem::instance()->getActiveWorld()->getEntitysInNode(Nodes::PlayerCameraSyncNode);

    for(int i = 0; i < xEntitys.size(); ++i)
    {
        GraphBodyCom *xGraphBodyCom;
        xGraphBodyCom = static_cast<GraphBodyCom*>(xEntitys.at(i)->getComponent(Components::GraphBodyCom));

        CameraTrackableCom *xCameraTrackableCom;
        xCameraTrackableCom = static_cast<CameraTrackableCom*>(xEntitys.at(i)->getComponent(Components::CameraTrackableCom));

        Ogre::SceneNode *xSceneNode;
        xSceneNode = xGraphBodyCom->mSceneNode;

        Ogre::Vector3 xPlayerPos;
        xPlayerPos = xSceneNode->getPosition();

        Ogre::Vector3 xNewCameraPos;
        xNewCameraPos = xCameraTrackableCom->mCamera->getPosition();
        xNewCameraPos.x = xPlayerPos.x;
        xNewCameraPos.y = xPlayerPos.y;

        xCameraTrackableCom->mCamera->setPosition(xNewCameraPos);
    }
}
