#include "PlayWorld.h"

#include "creators/ComponentsCreators.h"
#include "systems/PlayerControlSys.h"
#include "systems/AIControlSys.h"
#include "systems/PhysGraphSyncSys.h"
#include "systems/PlayerCameraSyncSys.h"
#include "systems/BulletsSys.h"
#include "systems/DamageSys.h"
#include "systems/PlayerGUISys.h"

#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <Utils.h>

unsigned int PlayWorld::mEnemysCount = 0;

PlayWorld::PlayWorld(QString xWorldName):World(xWorldName)
{
    this->addComponentToNode("PlayerControl", "GraphBodyCom");
    this->addComponentToNode("PlayerControl", "PhysBodyCom");
    this->addComponentToNode("PlayerControl", "WeaponCom");
    this->addComponentToNode("PlayerControl", "PlayerControllableCom");

    this->addComponentToNode("AIControl", "GraphBodyCom");
    this->addComponentToNode("AIControl", "PhysBodyCom");
    this->addComponentToNode("AIControl", "WeaponCom");
    this->addComponentToNode("AIControl", "AIControllableCom");

    this->addComponentToNode("PhysGraphSync", "GraphBodyCom");
    this->addComponentToNode("PhysGraphSync", "PhysBodyCom");

    this->addComponentToNode("PlayerCameraSync", "GraphBodyCom");
    this->addComponentToNode("PlayerCameraSync", "CameraTrackableCom");

    this->addComponentToNode("Bullets", "BulletCom");
    this->addComponentToNode("Bullets", "GraphBodyCom");
    this->addComponentToNode("Bullets", "PhysBodyCom");

    this->addComponentToNode("DoDamage", "BulletCom");
    this->addComponentToNode("DoDamage", "PhysBodyCom");

    this->addComponentToNode("Damageable", "HealthCom");
    this->addComponentToNode("Damageable", "PhysBodyCom");

    this->addComponentToNode("PlayerStat", "HealthCom");
    this->addComponentToNode("PlayerStat", "PlayerControllableCom");

    this->addComponentToNode("EnemyStat", "HealthCom");
    this->addComponentToNode("EnemyStat", "AIControllableCom");
    this->addComponentToNode("EnemyStat", "PhysBodyCom");

    this->addComponentToNode("GameGUI", "PlayerUICom");
}

PlayWorld::~PlayWorld()
{

}

void PlayWorld::load()
{
    //JGC::GraphicSystem::instance()->pauseRender();
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

            PhysBodyCom* xPhysBodyCom = cPlayerPhysBodyCom("PlayWorld");
            this->addComponent("Player", xPhysBodyCom);

            PlayerControllableCom* xPlayerControllableCom = cPlayerControllableCom();
            this->addComponent("Player", xPlayerControllableCom);

            CameraTrackableCom* xCameraTrackableCom = cCameraTrackableCom("PlayWorld", "MainCamera");
            this->addComponent("Player", xCameraTrackableCom);

            WeaponCom* xWeaponCom = cWeaponCom(0.3f);
            this->addComponent("Player", xWeaponCom);

            HealthCom *xHealthCom = cHealthCom(100,100);
            this->addComponent("Player", xHealthCom);
        }

        // Enemy
        {
            AIControllableCom* xAIControllableCom = cAIControllableCom();
            this->addComponent("Enemy", xAIControllableCom);

            GraphBodyCom* xGraphBodyCom = cEnemyGraphBodyCom("PlayWorld", "EnemyGraphBody", Ogre::Vector3(13,13,0));
            this->addComponent("Enemy", xGraphBodyCom);

            PhysBodyCom* xPhysBodyCom = cEnemyPhysBodyCom("PlayWorld", btVector3(13,13,0));
            this->addComponent("Enemy", xPhysBodyCom);

            WeaponCom* xWeaponCom = cWeaponCom(1.01f);
            this->addComponent("Enemy", xWeaponCom);

            HealthCom *xHealthCom = cHealthCom(100,100);
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

        PhysGraphSyncSys *xPhysGraphSyncSys;
        xPhysGraphSyncSys = new PhysGraphSyncSys();
        this->addSystem(5, xPhysGraphSyncSys);

        PlayerCameraSyncSys *xPlayerCameraSyncSys;
        xPlayerCameraSyncSys = new PlayerCameraSyncSys();
        this->addSystem(6, xPlayerCameraSyncSys);

        PlayerGUISys *xPlayerGUISys;
        xPlayerGUISys = new PlayerGUISys();
        this->addSystem(7, xPlayerGUISys);
    }

    //JGC::GraphicSystem::instance()->resumeRender();
    this->setWorldLoaded(true);
}

void PlayWorld::enter()
{
    JGC::GraphicSystem::instance()->setActiveSceneManager(this->getName());
    JGC::PhysicsSystem::instance()->setActiveDynamicsWorld(this->getName());
}

void PlayWorld::exit()
{

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

SoundBodyCom* PlayWorld::cWeaponComSoundBodyCom(short xObjectCollideWith, btVector3 xPosition, btQuaternion xOrientation)
{

}

void PlayWorld::dSoundBodyCom(SoundBodyCom* xSoundBodyCom)
{

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

void PlayWorld::dCameraTrackableCom(QString xSceneManagerName)
{

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
