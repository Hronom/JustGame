#include "MainSystem.h"

MainSystem::MainSystem()
{
	mNeedShutdown = false;

	mGraphicSystem = new GraphicSystem(this);
	mPhysicsSystem = new PhysicsSystem(this);
	mInputSystem = new InputSystem(this);
	mStatesSystem = new StatesSystem();
}

MainSystem::~MainSystem()
{
	delete mStatesSystem;
	delete mInputSystem;
	delete mPhysicsSystem;
	delete mGraphicSystem;
}

bool MainSystem::init()
{
	mGraphicSystem->init();
	mPhysicsSystem->init(mGraphicSystem->getSceneManager());
	mInputSystem->init(mGraphicSystem->getWinHandle(), mGraphicSystem->getWinWidth(), mGraphicSystem->getWinHeight());
	mStatesSystem->init();

	return true;
}

void MainSystem::run()
{
	mGraphicSystem->start();
}

void MainSystem::addState(int xNumber, iState *xState)
{
	mStatesSystem->addState(xNumber, xState);
}

//-------------------------------------------------------------
// iMainListener
//-------------------------------------------------------------
bool MainSystem::frameStarted(const Ogre::FrameEvent& evt)
{
	mPhysicsSystem->needUpdate(evt);
	mInputSystem->needUpdate();
	mStatesSystem->needUpdate(evt);

	return !mNeedShutdown;
}

void MainSystem::windowResized(unsigned int xNewWidth, unsigned int xNewHeight)
{
	mInputSystem->injectWindowResized(xNewWidth, xNewHeight);
}

void MainSystem::windowClosed()
{
	mNeedShutdown = true;
}

void MainSystem::mouseMoved(const OIS::MouseEvent& e)
{
	mGraphicSystem->injectMouseMoved(e);
	mStatesSystem->injectMouseMoved(e);
}

void MainSystem::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGraphicSystem->injectMousePressed(e, id);
	mStatesSystem->injectMousePressed(e, id);
}

void MainSystem::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGraphicSystem->injectMouseReleased(e, id);
	mStatesSystem->injectMouseReleased(e, id);
}

void MainSystem::keyPressed(const OIS::KeyEvent& e)
{
	mGraphicSystem->injectKeyPressed(e);
	mStatesSystem->injectKeyPressed(e);
}

void MainSystem::keyReleased(const OIS::KeyEvent& e)
{
	mGraphicSystem->injectKeyReleased(e);
	mStatesSystem->injectKeyReleased(e);
}

//-------------------------------------------------------------
// iCore
//-------------------------------------------------------------
void MainSystem::needSwitchToStateId(int xStateId)
{
	mStatesSystem->switchToState(xStateId);
}

void MainSystem::needShutdown()
{
	mNeedShutdown = true;
}

void MainSystem::loadGUILayout(Ogre::String xLayoutName)
{
	mGraphicSystem->loadLayout(xLayoutName);
}

void MainSystem::unloadGUILayout()
{
	mGraphicSystem->unloadLayout();
}

void MainSystem::addButtonDelegate(Ogre::String xButtonName, iState *xState)
{
	mGraphicSystem->addButtonDelegate(xButtonName, xState);
}

Ogre::SceneManager* MainSystem::getSceneManager()
{
	return mGraphicSystem->getSceneManager();
}

Ogre::Camera* MainSystem::getCamera()
{
	return mGraphicSystem->getCamera();
}

OgreBulletDynamics::DynamicsWorld* MainSystem::getDynamicsWorld()
{
	return mPhysicsSystem->getDynamicsWorld();
}