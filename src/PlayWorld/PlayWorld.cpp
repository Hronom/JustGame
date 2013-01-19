#include "PlayWorld.h"

#include "systems/PlayerControlSys.h"
#include "systems/AIControlSys.h"
#include "systems/PhysGraphSyncSys.h"
#include "systems/PhysSoundSyncSys.h"
#include "systems/PlayerCameraSyncSys.h"
#include "systems/BulletsSys.h"
#include "systems/DamageSys.h"
#include "systems/PlayerGUISys.h"
#include "systems/EnemyDeathSys.h"
#include "systems/EnemySpawner.h"
#include "systems/PlayerDeathSys.h"
#include "systems/PlayerWinLoseSys.h"

#include <GraphicSystem.h>
#include <SoundSystem.h>
#include <PhysicsSystem.h>
#include <Utils.h>

unsigned int PlayWorld::mEnemysCount = 0;

PlayWorld::PlayWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode<GraphBodyCom>(Nodes::PlayerControlNode);
    this->addComponentToNode<SoundBodyCom>(Nodes::PlayerControlNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::PlayerControlNode);
    this->addComponentToNode<WeaponCom>(Nodes::PlayerControlNode);
    this->addComponentToNode<PlayerControllableCom>(Nodes::PlayerControlNode);

    this->addComponentToNode<GraphBodyCom>(Nodes::AIControlNode);
    this->addComponentToNode<SoundBodyCom>(Nodes::AIControlNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::AIControlNode);
    this->addComponentToNode<WeaponCom>(Nodes::AIControlNode);
    this->addComponentToNode<AIControllableCom>(Nodes::AIControlNode);

    this->addComponentToNode<GraphBodyCom>(Nodes::PhysGraphSyncNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::PhysGraphSyncNode);

    this->addComponentToNode<SoundBodyCom>(Nodes::PhysSoundSyncNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::PhysSoundSyncNode);

    this->addComponentToNode<SoundListenerCom>(Nodes::PhysSoundListenerSyncNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::PhysSoundListenerSyncNode);

    this->addComponentToNode<GraphBodyCom>(Nodes::PlayerCameraSyncNode);
    this->addComponentToNode<CameraTrackableCom>(Nodes::PlayerCameraSyncNode);

    this->addComponentToNode<BulletCom>(Nodes::BulletsNode);
    this->addComponentToNode<GraphBodyCom>(Nodes::BulletsNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::BulletsNode);

    this->addComponentToNode<BulletCom>(Nodes::DoDamageNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::DoDamageNode);

    this->addComponentToNode<HealthCom>(Nodes::DamageableNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::DamageableNode);

    this->addComponentToNode<HealthCom>(Nodes::PlayerStatNode);
    this->addComponentToNode<PlayerControllableCom>(Nodes::PlayerStatNode);

    this->addComponentToNode<HealthCom>(Nodes::EnemyStatNode);
    this->addComponentToNode<AIControllableCom>(Nodes::EnemyStatNode);
    this->addComponentToNode<PhysBodyCom>(Nodes::EnemyStatNode);

    this->addComponentToNode<PlayerUICom>(Nodes::GameGUINode);
}

PlayWorld::~PlayWorld()
{
    this->removeComponentFromNode<GraphBodyCom>(Nodes::PlayerControlNode);
    this->removeComponentFromNode<SoundBodyCom>(Nodes::PlayerControlNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::PlayerControlNode);
    this->removeComponentFromNode<WeaponCom>(Nodes::PlayerControlNode);
    this->removeComponentFromNode<PlayerControllableCom>(Nodes::PlayerControlNode);

    this->removeComponentFromNode<GraphBodyCom>(Nodes::AIControlNode);
    this->removeComponentFromNode<SoundBodyCom>(Nodes::AIControlNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::AIControlNode);
    this->removeComponentFromNode<WeaponCom>(Nodes::AIControlNode);
    this->removeComponentFromNode<AIControllableCom>(Nodes::AIControlNode);

    this->removeComponentFromNode<GraphBodyCom>(Nodes::PhysGraphSyncNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::PhysGraphSyncNode);

    this->removeComponentFromNode<SoundBodyCom>(Nodes::PhysSoundSyncNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::PhysSoundSyncNode);

    this->removeComponentFromNode<SoundListenerCom>(Nodes::PhysSoundListenerSyncNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::PhysSoundListenerSyncNode);

    this->removeComponentFromNode<GraphBodyCom>(Nodes::PlayerCameraSyncNode);
    this->removeComponentFromNode<CameraTrackableCom>(Nodes::PlayerCameraSyncNode);

    this->removeComponentFromNode<BulletCom>(Nodes::BulletsNode);
    this->removeComponentFromNode<GraphBodyCom>(Nodes::BulletsNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::BulletsNode);

    this->removeComponentFromNode<BulletCom>(Nodes::DoDamageNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::DoDamageNode);

    this->removeComponentFromNode<HealthCom>(Nodes::DamageableNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::DamageableNode);

    this->removeComponentFromNode<HealthCom>(Nodes::PlayerStatNode);
    this->removeComponentFromNode<PlayerControllableCom>(Nodes::PlayerStatNode);

    this->removeComponentFromNode<HealthCom>(Nodes::EnemyStatNode);
    this->removeComponentFromNode<AIControllableCom>(Nodes::EnemyStatNode);
    this->removeComponentFromNode<PhysBodyCom>(Nodes::EnemyStatNode);

    this->removeComponentFromNode<PlayerUICom>(Nodes::GameGUINode);
}

void PlayWorld::enter()
{
    {
        JGC::GraphicSystem::instance()->createSceneManager(this->getName());
        JGC::PhysicsSystem::instance()->createDynamicsWorld(this->getName());
    }

    // Make entitys
    {
        GraphBodyCom* xBackgroundGraphBodyCom = cBackgroundGraphBodyCom("PlayWorld", "Background");
        this->addComponent("Background", xBackgroundGraphBodyCom);

        // Player
        {
            GraphBodyCom* xGraphBodyCom = cPlayerGraphBodyCom("PlayWorld", "PlayerGraphBody");
            this->addComponent("Player", xGraphBodyCom);

            SoundBodyCom* xSoundBodyCom = cWeaponSoundBodyCom();
            this->addComponent("Player", xSoundBodyCom);

            SoundListenerCom* xSoundListenerCom = cSoundListenerCom();
            this->addComponent("Player", xSoundListenerCom);

            PhysBodyCom* xPhysBodyCom = cPlayerPhysBodyCom("PlayWorld");
            this->addComponent("Player", xPhysBodyCom);

            PlayerControllableCom* xPlayerControllableCom = cPlayerControllableCom();
            this->addComponent("Player", xPlayerControllableCom);

            CameraTrackableCom* xCameraTrackableCom = cCameraTrackableCom("PlayWorld", "MainCamera");
            this->addComponent("Player", xCameraTrackableCom);

            WeaponCom* xWeaponCom = cWeaponCom(0.1f);
            this->addComponent("Player", xWeaponCom);

            HealthCom *xHealthCom = cHealthCom(10, 10);
            this->addComponent("Player", xHealthCom);
        }

        // Enemy
        {
            AIControllableCom* xAIControllableCom = cAIControllableCom();
            this->addComponent("Enemy", xAIControllableCom);

            GraphBodyCom* xGraphBodyCom = cEnemyGraphBodyCom("PlayWorld", "EnemyGraphBody", Ogre::Vector3(13,13,0));
            this->addComponent("Enemy", xGraphBodyCom);

            SoundBodyCom* xSoundBodyCom = cWeaponSoundBodyCom();
            this->addComponent("Enemy", xSoundBodyCom);

            PhysBodyCom* xPhysBodyCom = cEnemyPhysBodyCom("PlayWorld", btVector3(13,13,0));
            this->addComponent("Enemy", xPhysBodyCom);

            WeaponCom* xWeaponCom = cWeaponCom(1.01f);
            this->addComponent("Enemy", xWeaponCom);

            HealthCom *xHealthCom = cHealthCom(10, 10);
            this->addComponent("Enemy", xHealthCom);
        }

        // GUI
        {
            PlayerUICom *xPlayerUICom = cPlayerUICom();
            this->addComponent("GUI", xPlayerUICom);
        }

    }

    // Make systems
    {
        EnemySpawner *xEnemySpawner;
        xEnemySpawner = new EnemySpawner();
        this->addSystem(0, xEnemySpawner);

        PlayerControlSys *xPlayerControlSys;
        xPlayerControlSys = new PlayerControlSys();
        this->addSystem(1, xPlayerControlSys);

        AIControlSys *xAIControlSys;
        xAIControlSys = new AIControlSys();
        this->addSystem(2, xAIControlSys);

        BulletsSys *xBulletsSys;
        xBulletsSys = new BulletsSys();
        this->addSystem(3, xBulletsSys);

        DamageSys *xDamageSys;
        xDamageSys = new DamageSys();
        this->addSystem(4, xDamageSys);

        EnemyDeathSys *xEnemyDeathSys;
        xEnemyDeathSys = new EnemyDeathSys();
        this->addSystem(5, xEnemyDeathSys);

        PlayerDeathSys *xPlayerDeathSys;
        xPlayerDeathSys = new PlayerDeathSys();
        this->addSystem(6, xPlayerDeathSys);

        PlayerWinLoseSys *xPlayerWinLoseSys;
        xPlayerWinLoseSys = new PlayerWinLoseSys();
        this->addSystem(7, xPlayerWinLoseSys);

        PhysGraphSyncSys *xPhysGraphSyncSys;
        xPhysGraphSyncSys = new PhysGraphSyncSys();
        this->addSystem(8, xPhysGraphSyncSys);

        PhysSoundSyncSys *xPhysSoundSyncSys;
        xPhysSoundSyncSys = new PhysSoundSyncSys();
        this->addSystem(9, xPhysSoundSyncSys);

        PlayerCameraSyncSys *xPlayerCameraSyncSys;
        xPlayerCameraSyncSys = new PlayerCameraSyncSys();
        this->addSystem(10, xPlayerCameraSyncSys);

        PlayerGUISys *xPlayerGUISys;
        xPlayerGUISys = new PlayerGUISys();
        this->addSystem(11, xPlayerGUISys);
    }

    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    JGC::PhysicsSystem::instance()->setActiveDynamicsWorld(this->getName());

    this->setWorldActive(true);
}

void PlayWorld::exit()
{
    // Delete systems
    {
        QList<JGC::ISystem*> xSystems;
        xSystems = this->getAllSystems();
        while(!xSystems.empty())
        {
            JGC::ISystem *xSystem;
            xSystem = xSystems.takeFirst();
            this->removeSystem(xSystem);
            delete xSystem;
        }
    }

    // Delete entitys
    {
        QList<JGC::Entity*> xEntitys;
        xEntitys = this->getAllEntitys();
        while(!xEntitys.empty())
        {
            JGC::Entity *xEntity;
            xEntity = xEntitys.takeFirst();

            GraphBodyCom* xGraphBodyCom;
            xGraphBodyCom = xEntity->getComponent<GraphBodyCom>();
            if(xGraphBodyCom != NULL)
            {
                dGraphBodyCom(this->getName(), xGraphBodyCom);
                this->removeComponent(xEntity->getName(), xGraphBodyCom);
            }

            SoundBodyCom* xSoundBodyCom;
            xSoundBodyCom = xEntity->getComponent<SoundBodyCom>();
            if(xSoundBodyCom != NULL)
            {
                dWeaponSoundBodyCom(xSoundBodyCom);
                this->removeComponent(xEntity->getName(), xSoundBodyCom);
            }

            SoundListenerCom* xSoundListenerCom;
            xSoundListenerCom = xEntity->getComponent<SoundListenerCom>();
            if(xSoundListenerCom != NULL)
            {
                dSoundListenerCom(xSoundListenerCom);
                this->removeComponent(xEntity->getName(), xSoundListenerCom);
            }

            PhysBodyCom* xPhysBodyCom;
            xPhysBodyCom = xEntity->getComponent<PhysBodyCom>();
            if(xPhysBodyCom != NULL)
            {
                dPhysBodyCom(this->getName(), xPhysBodyCom);
                this->removeComponent(xEntity->getName(), xPhysBodyCom);
            }

            PlayerControllableCom* xPlayerControllableCom;
            xPlayerControllableCom = xEntity->getComponent<PlayerControllableCom>();
            if(xPlayerControllableCom != NULL)
            {
                this->removeComponent(xEntity->getName(), xPlayerControllableCom);
            }

            CameraTrackableCom* xCameraTrackableCom;
            xCameraTrackableCom = xEntity->getComponent<CameraTrackableCom>();
            if(xCameraTrackableCom != NULL)
            {
                //dCameraTrackableCom(this->getName(), xCameraTrackableCom);
                this->removeComponent(xEntity->getName(), xCameraTrackableCom);
            }

            WeaponCom* xWeaponCom;
            xWeaponCom = xEntity->getComponent<WeaponCom>();
            if(xWeaponCom != NULL)
            {
                //dWeaponCom(xWeaponCom);
                this->removeComponent(xEntity->getName(), xWeaponCom);
            }

            HealthCom* xHealthCom;
            xHealthCom = xEntity->getComponent<HealthCom>();
            if(xHealthCom != NULL)
            {
                //dHea(xHealthCom);
                this->removeComponent(xEntity->getName(), xHealthCom);
            }

            AIControllableCom* xAIControllableCom;
            xAIControllableCom = xEntity->getComponent<AIControllableCom>();
            if(xAIControllableCom != NULL)
            {
                //dAI(xAIControllableCom);
                this->removeComponent(xEntity->getName(), xAIControllableCom);
            }

            PlayerUICom* xPlayerUICom;
            xPlayerUICom = xEntity->getComponent<PlayerUICom>();
            if(xPlayerUICom != NULL)
            {
                dPlayerUICom(xPlayerUICom);
                this->removeComponent(xEntity->getName(), xPlayerUICom);
            }

            this->removeEntity(xEntity->getName());
        }
    }

    {
        JGC::GraphicSystem::instance()->deleteSceneManager(this->getName());
        JGC::PhysicsSystem::instance()->deleteDynamicsWorld(this->getName());
    }

    this->setWorldActive(false);
}

GraphBodyCom* PlayWorld::cBackgroundGraphBodyCom(QString xSceneManagerName, QString xComponentName)
{
    // create ManualObject
    Ogre::ManualObject *xManualObject;
    xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());

    Ogre::ColourValue xColor = Ogre::ColourValue(0.104f, 0.234f, 0.140f, 0.0f);
    Ogre::Real xGridDistance = 10.0f;
    for (Ogre::Real i = -50.0f; i < 50.0f; i+=1.0f)
    {
        // Draw vertical line
        xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
        xManualObject->position(i * xGridDistance, -500.0f, -100.0f);
        xManualObject->colour(xColor);
        xManualObject->position(i * xGridDistance, +500.0f, -100.0f);
        xManualObject->colour(xColor);
        xManualObject->end();
        // Draw gorizontal line
        xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
        xManualObject->position(-500.0f, i * xGridDistance, -100.0f);
        xManualObject->colour(xColor);
        xManualObject->position(+500.0f, i * xGridDistance, -100.0f);
        xManualObject->colour(xColor);
        xManualObject->end();
    }
    xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

    // create Entity
    Ogre::Entity *xEntity;
    xEntity = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());

    // create SceneNode
    Ogre::SceneNode *xSceneNode;
    xSceneNode = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
    // connect Entity to Node
    xSceneNode->attachObject(xEntity);

    // create component
    GraphBodyCom* xGraphBodyCom;
    xGraphBodyCom = new GraphBodyCom();

    xGraphBodyCom->mManualObject = xManualObject;
    xGraphBodyCom->mEntity = xEntity;
    xGraphBodyCom->mSceneNode = xSceneNode;

    return xGraphBodyCom;
}

GraphBodyCom* PlayWorld::cPlayerGraphBodyCom(QString xSceneManagerName, QString xComponentName)
{
    Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 1.0, 1.0, 0.0);
    // create ManualObject
    Ogre::ManualObject *xManualObject;
    xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    const float xObjectRadius  = 5;
    const float xAccuracy = 5;
    unsigned xPoint_index = 0;
    for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy)
    {
        xManualObject->position(xObjectRadius * cos(xTheta), xObjectRadius * sin(xTheta), 0);
        xManualObject->colour(xColor);
        xManualObject->index(xPoint_index++);
    }
    xManualObject->index(0); // Rejoins the last point to the first.
    xManualObject->end();
    xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

    // create Entity
    Ogre::Entity *xEntity;
    xEntity = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
    xEntity->setUserAny(Ogre::Any(new int(0)));
    // create SceneNode
    Ogre::SceneNode *xSceneNode;
    xSceneNode = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
    // connect Entity to Node
    xSceneNode->attachObject(xEntity);

    Ogre::Vector3 xPosition = Ogre::Vector3(0, 0, 0);
    xSceneNode->setPosition(xPosition);

    Ogre::Quaternion xOrientation = Ogre::Quaternion(0, 0, 0, 1);
    xSceneNode->setOrientation(xOrientation);

    // create component
    GraphBodyCom* xGraphBodyCom;
    xGraphBodyCom = new GraphBodyCom();

    xGraphBodyCom->mManualObject = xManualObject;
    xGraphBodyCom->mEntity = xEntity;
    xGraphBodyCom->mSceneNode = xSceneNode;

    return xGraphBodyCom;
}

GraphBodyCom* PlayWorld::cEnemyGraphBodyCom(QString xSceneManagerName, QString xComponentSuffix, Ogre::Vector3 xPosition)
{
    QString xComponentName;
    xComponentName = xComponentSuffix;
    xComponentName += QString::number(mEnemysCount);
    mEnemysCount++;

    Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 1.0, 1.0, 0.0);
    // create ManualObject
    Ogre::ManualObject *xManualObject;
    xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
    // accuracy is the count of points (and lines).
    // Higher values make the circle smoother, but may slowdown the performance.
    // The performance also is related to the count of circles.
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    const float xObjectRadius  = 7;
    const float xAccuracy = 1.5;//35
    unsigned xPoint_index = 0;
    for(float xTheta = 0; xTheta <= 2 * Ogre::Math::PI; xTheta += Ogre::Math::PI / xAccuracy)
    {
        xManualObject->position(xObjectRadius * cos(xTheta), xObjectRadius * sin(xTheta), 0);
        xManualObject->colour(xColor);
        xManualObject->index(xPoint_index++);
    }
    xManualObject->index(0); // Rejoins the last point to the first.
    xManualObject->end();
    xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

    // create Entity
    Ogre::Entity *xEntity;
    xEntity = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
    // create SceneNode
    Ogre::SceneNode *xSceneNode;
    xSceneNode = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
    // Set position of SceneNode
    xSceneNode->setPosition(xPosition);

    // connect Entity to Node
    xSceneNode->attachObject(xEntity);

    // create component
    GraphBodyCom *xGraphBodyCom;
    xGraphBodyCom = new GraphBodyCom();
    xGraphBodyCom->mManualObject = xManualObject;
    xGraphBodyCom->mEntity = xEntity;
    xGraphBodyCom->mSceneNode = xSceneNode;

    xEntity->setUserAny(Ogre::Any(xGraphBodyCom));

    return xGraphBodyCom;
}

GraphBodyCom* PlayWorld::cBulletGraphBodyCom(QString xSceneManagerName, QString xComponentName, Ogre::Vector3 xPosition, Ogre::Vector3 xDestination)
{
    Ogre::ColourValue xColor = Ogre::ColourValue(1.0, 0.0, 0.0, 0.0);
    Ogre::ManualObject *xManualObject;
    xManualObject = new Ogre::ManualObject((xComponentName+"_Manual").toStdString());
    xManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    xManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));
    xManualObject->colour(xColor);
    xManualObject->position(Ogre::Vector3(-1.5f,0.3f,0.0f));
    xManualObject->colour(xColor);
    xManualObject->position(Ogre::Vector3(1.5f,0.3f,0.0f));
    xManualObject->colour(xColor);
    xManualObject->position(Ogre::Vector3(1.5f,-0.3f,0.0f));
    xManualObject->colour(xColor);
    xManualObject->position(Ogre::Vector3(-1.5f,-0.3f,0.0f));
    xManualObject->colour(xColor);
    xManualObject->end();
    xManualObject->convertToMesh((xComponentName+"_Mesh").toStdString());

    // create Entity
    Ogre::Entity *xEntity;
    xEntity = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->createEntity((xComponentName+"_Entity").toStdString(), (xComponentName+"_Mesh").toStdString());
    xEntity->setUserAny(Ogre::Any(new int(0)));
    // create SceneNode
    Ogre::SceneNode *xSceneNode;
    xSceneNode = JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->getRootSceneNode()->createChildSceneNode((xComponentName+"_Node").toStdString());
    // Set position of SceneNode
    xSceneNode->setPosition(xPosition);
    // Rotate SceneNode
    Ogre::Vector3 xDirection = xDestination - xPosition;
    Ogre::Vector3 xSrc = xSceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
    Ogre::Quaternion xQuat = xSrc.getRotationTo(xDirection);
    xSceneNode->rotate(xQuat);

    // connect Entity to Node
    xSceneNode->attachObject(xEntity);

    // create component
    GraphBodyCom* xGraphBodyCom;
    xGraphBodyCom = new GraphBodyCom();

    xGraphBodyCom->mManualObject = xManualObject;
    xGraphBodyCom->mEntity = xEntity;
    xGraphBodyCom->mSceneNode = xSceneNode;

    return xGraphBodyCom;
}

void PlayWorld::dGraphBodyCom(QString xSceneManagerName, GraphBodyCom* xGraphBodyCom)
{
    JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->destroyManualObject(xGraphBodyCom->mManualObject);
    JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->destroyEntity(xGraphBodyCom->mEntity);
    xGraphBodyCom->mSceneNode->removeAndDestroyAllChildren();
    JGC::GraphicSystem::instance()->getSceneManager(xSceneManagerName)->destroySceneNode(xGraphBodyCom->mSceneNode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PhysBodyCom* PlayWorld::cPlayerPhysBodyCom(QString xDynamicsWorldName)
{
    // after that create the BulletCom shape with the calculated xSize
    float xObjectRadius = 5;

    btCollisionShape *xCollisionShape;
    xCollisionShape = new btSphereShape(xObjectRadius);
    // and the BulletCom rigid body
    btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)));
    btRigidBody *xRigidBody;
    xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0, 0, 0));
    xRigidBody->setRestitution(0.0f);
    xRigidBody->setFriction(0.5f);
    xRigidBody->setLinearFactor(btVector3(1, 1, 0));
    xRigidBody->setAngularFactor(btVector3(0, 0, 1));

    JGC::PhysicsSystem::instance()->getDynamicsWorld(xDynamicsWorldName)->addRigidBody(xRigidBody, PLAYER_GROUP, PLAYER_GROUP | ENEMY_GROUP | BulletCom_GROUP);

    // create component
    PhysBodyCom* xPhysBodyCom;
    xPhysBodyCom = new PhysBodyCom();

    xRigidBody->setUserPointer(xPhysBodyCom);

    xPhysBodyCom->mCollisionShape = xCollisionShape;
    xPhysBodyCom->mRigidBody = xRigidBody;

    return xPhysBodyCom;
}

PhysBodyCom* PlayWorld::cEnemyPhysBodyCom(QString xDynamicsWorldName, btVector3 xPosition)
{
    // after that create the BulletCom shape with the calculated xSize
    float xObjectRadius = 7;

    btCollisionShape *xCollisionShape;
    xCollisionShape = new btSphereShape(xObjectRadius);
    // and the BulletCom rigid body
    btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), xPosition));
    btRigidBody *xRigidBody;
    xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0,0,0));
    xRigidBody->setRestitution(0.0f);
    xRigidBody->setFriction(0.5f);
    xRigidBody->setLinearFactor(btVector3(1,1,0));
    xRigidBody->setAngularFactor(btVector3(0, 0, 1));

    JGC::PhysicsSystem::instance()->getDynamicsWorld(xDynamicsWorldName)->addRigidBody(xRigidBody, ENEMY_GROUP, PLAYER_GROUP | ENEMY_GROUP | BulletCom_GROUP);

    // create component
    PhysBodyCom* xPhysBodyCom;
    xPhysBodyCom = new PhysBodyCom();

    xRigidBody->setUserPointer(xPhysBodyCom);

    xPhysBodyCom->mCollisionShape = xCollisionShape;
    xPhysBodyCom->mRigidBody = xRigidBody;

    return xPhysBodyCom;
}

PhysBodyCom* PlayWorld::cBulletPhysBodyCom(QString xDynamicsWorldName, short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation)
{
    Ogre::Vector3 xBoundingBoxSize = Ogre::Vector3(3.5f, 3.5f, 0);	// xSize of the box
    xBoundingBoxSize.z = 3.0f;
    xBoundingBoxSize /= 2.0f; // only the half needed
    xBoundingBoxSize *= 0.95f;	// BulletCom margin is a bit bigger so we need a smaller xSize

    // after that create the BulletCom shape with the calculated xSize
    btVector3 xSize;
    xSize = JGC::Utils::toBtVector3(xBoundingBoxSize);

    btCollisionShape *xCollisionShape;
    xCollisionShape = new btBoxShape(xSize);
    // and the BulletCom rigid body
    btDefaultMotionState* xMotionState = new btDefaultMotionState(btTransform(xOrientation, xPosition));
    btRigidBody *xRigidBody;
    xRigidBody = new btRigidBody(0.1f, xMotionState, xCollisionShape, btVector3(0,0,0));
    xRigidBody->setRestitution(0.0f);
    xRigidBody->setFriction(0.5f);
    xRigidBody->setLinearFactor(btVector3(1,1,0));
    xRigidBody->setAngularFactor(btVector3(0, 0, 1));

    JGC::PhysicsSystem::instance()->getDynamicsWorld(xDynamicsWorldName)->addRigidBody(xRigidBody, BulletCom_GROUP, xObjectCollideWith | BulletCom_GROUP);

    // MOVE
    Ogre::Vector3 xVector;
    float xMoveSpeed = 5.0f;
    xVector = Ogre::Vector3(1,0,0) * xMoveSpeed;
    xVector =  JGC::Utils::toOgreQuaternion(xOrientation) * xVector;
    xRigidBody->applyCentralImpulse(JGC::Utils::toBtVector3(xVector));

    // create component
    PhysBodyCom* xPhysBodyCom;
    xPhysBodyCom = new PhysBodyCom();

    xRigidBody->setUserPointer(xPhysBodyCom);

    xPhysBodyCom->mCollisionShape = xCollisionShape;
    xPhysBodyCom->mRigidBody = xRigidBody;

    return xPhysBodyCom;
}

void PlayWorld::dPhysBodyCom(QString xDynamicsWorldName, PhysBodyCom* xPhysBodyCom)
{
    JGC::PhysicsSystem::instance()->getDynamicsWorld(xDynamicsWorldName)->removeRigidBody(xPhysBodyCom->mRigidBody);
    delete xPhysBodyCom->mRigidBody->getMotionState();
    delete xPhysBodyCom->mRigidBody;
    delete xPhysBodyCom->mCollisionShape;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SoundBodyCom* PlayWorld::cWeaponSoundBodyCom()
{
    JGC::SoundSource *xSoundSource = JGC::SoundSystem::instance()->createSoundSource(0, 0, 0, "../Media/Sound/impulse.wav", false);

    // create component
    SoundBodyCom* xSoundBodyCom;
    xSoundBodyCom = new SoundBodyCom();
    xSoundBodyCom->mSoundSource = xSoundSource;

    return xSoundBodyCom;
}

void PlayWorld::dWeaponSoundBodyCom(SoundBodyCom* xSoundBodyCom)
{
    JGC::SoundSystem::instance()->destroySoundSource(xSoundBodyCom->mSoundSource);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SoundListenerCom* PlayWorld::cSoundListenerCom()
{
    JGC::SoundListener *xSoundListener = JGC::SoundSystem::instance()->getSoundListener();

    // create component
    SoundListenerCom* xSoundListenerCom;
    xSoundListenerCom = new SoundListenerCom();
    xSoundListenerCom->mSoundListener = xSoundListener;

    return xSoundListenerCom;
}

void PlayWorld::dSoundListenerCom(SoundListenerCom* xSoundListenerCom)
{
    //JGC::SoundSystem::instance()->destroySoundSource(xSoundBodyCom->mSoundSource);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraTrackableCom* PlayWorld::cCameraTrackableCom(QString xSceneManagerName, QString xCameraName)
{
    Ogre::Camera* xCamera;
    xCamera = JGC::GraphicSystem::instance()->getCamera(xSceneManagerName);

    // create component
    CameraTrackableCom* xCameraTrackableCom;
    xCameraTrackableCom = new CameraTrackableCom();

    xCameraTrackableCom->mCamera = xCamera;

    return xCameraTrackableCom;
}

HealthCom* PlayWorld::cHealthCom(qint32 xHealthComCurrent, qint32 xHealthComTotal)
{
    // create component
    HealthCom* xHealthCom;
    xHealthCom = new HealthCom();

    xHealthCom->mHealthTotal = xHealthComTotal;
    xHealthCom->mHealthCurrent = xHealthComCurrent;

    return xHealthCom;
}

PlayerControllableCom* PlayWorld::cPlayerControllableCom()
{
    // create component
    PlayerControllableCom* xPlayerControllableCom;
    xPlayerControllableCom = new PlayerControllableCom();

    return xPlayerControllableCom;
}

AIControllableCom* PlayWorld::cAIControllableCom()
{
    // create component
    AIControllableCom* xAIControllableCom;
    xAIControllableCom = new AIControllableCom();

    return xAIControllableCom;
}

WeaponCom* PlayWorld::cWeaponCom(float xShootDelay)
{
    // create component
    WeaponCom* xWeaponCom;
    xWeaponCom = new WeaponCom();
    xWeaponCom->mShootDelay = xShootDelay;
    xWeaponCom->mTimeSinceLastShot = xShootDelay;

    return xWeaponCom;
}

BulletCom* PlayWorld::cBulletCom(float xTotalLiveTime, qint32 xDamage)
{
    // create component
    BulletCom* xBulletCom;
    xBulletCom = new BulletCom();
    xBulletCom->mTotalLiveTime = xTotalLiveTime;
    xBulletCom->mLiveTime = 0;
    xBulletCom->mDamageCount = xDamage;

    return xBulletCom;
}

void PlayWorld::dBulletCom(BulletCom *xBulletCom)
{
    delete xBulletCom;
}

PlayerUICom* PlayWorld::cPlayerUICom()
{
    MyGUI::VectorWidgetPtr xCurrentLayoutWidgets;
    xCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("GameUI.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
    xCurrentLayoutWidgets[0]->setVisible(true);

    MyGUI::ProgressBar *xPlayerHealthBar;
    xPlayerHealthBar = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::ProgressBar>("PlayerHealthBar");

    MyGUI::Widget *xEnemyPanel;
    xEnemyPanel = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::Widget>("EnemyStatPanel");
    xEnemyPanel->setVisible(false);

    MyGUI::ProgressBar *xEnemyHealthBar;
    xEnemyHealthBar = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::ProgressBar>("EnemyHealthBar");

    // Create component
    PlayerUICom* xPlayerUICom;
    xPlayerUICom = new PlayerUICom();
    xPlayerUICom->mLayoutWidgets = xCurrentLayoutWidgets;
    xPlayerUICom->mPlayerHealthBar = xPlayerHealthBar;
    xPlayerUICom->mEnemyPanel = xEnemyPanel;
    xPlayerUICom->mEnemyHealthBar = xEnemyHealthBar;

    return xPlayerUICom;
}

void PlayWorld::dPlayerUICom(PlayerUICom* xPlayerUICom)
{
    MyGUI::PointerManager::getInstancePtr()->setPointer("Arrow");
    if(xPlayerUICom->mLayoutWidgets.size() != 0)
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(xPlayerUICom->mLayoutWidgets);
        xPlayerUICom->mLayoutWidgets.clear();
    }
}
