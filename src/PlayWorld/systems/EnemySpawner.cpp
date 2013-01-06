#include "EnemySpawner.h"

#include <InputSystem.h>
#include <GraphicSystem.h>
#include <WorldsSystem.h>
#include <CountersSystem.h>
#include <IComponent.h>
#include <Utils.h>
#include <Entity.h>

#include "QDebug"

#include "../PlayWorld.h"

EnemySpawner::EnemySpawner()
{
    buttonDawn = false;
    JGC::CountersSystem::instance()->addCounter("EnemyCount");
}

EnemySpawner::~EnemySpawner()
{
    JGC::CountersSystem::instance()->removeCounter("EnemyCount");
}

void EnemySpawner::injectUpdate(const float &xTimeSinceLastUpdate)
{
    // Enemy
    if(JGC::InputSystem::instance()->isKeyDown(OIS::KC_E))
    {
        if(buttonDawn == false)
        {
            buttonDawn = true;

            int xPosX;
            xPosX = qrand() % 100;
            int xPosY;
            xPosY = qrand() % 100;

            QString xEnemyName;
            xEnemyName = JGC::CountersSystem::instance()->getNameWithSuffix("EnemyCount", "Enemy");

            AIControllableCom* xAIControllableCom = PlayWorld::cAIControllableCom();
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xAIControllableCom);

            GraphBodyCom* xGraphBodyCom = PlayWorld::cEnemyGraphBodyCom("PlayWorld", xEnemyName, Ogre::Vector3(xPosX,xPosY,0));
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xGraphBodyCom);

            SoundBodyCom* xSoundBodyCom = PlayWorld::cWeaponSoundBodyCom();
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xSoundBodyCom);

            PhysBodyCom* xPhysBodyCom = PlayWorld::cEnemyPhysBodyCom("PlayWorld", btVector3(xPosX,xPosY,0));
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xPhysBodyCom);

            WeaponCom* xWeaponCom = PlayWorld::cWeaponCom(1.01f);
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xWeaponCom);

            HealthCom *xHealthCom = PlayWorld::cHealthCom(10, 10);
            JGC::WorldsSystem::instance()->getActiveWorld()->addComponent(xEnemyName, xHealthCom);
        }
    }
    else
         buttonDawn = false;
}
