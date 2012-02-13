#include "MainSystem.h"

MainSystem::MainSystem()
{
	mGraphicSystem = new GraphicSystem(this);
	mPhysicsSystem = new PhysicsSystem(this);
	mInputSystem = new InputSystem(this);
	mStatesSystem = new StatesSystem(this);

	mNeedShutdown = false;
	mStateLoad = false;
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

void  MainSystem::setLoadState(iLoadState *xLoadState)
{
	mStatesSystem->setLoadState(xLoadState);
}

void MainSystem::addNormalState(int xNumber, iState *xState)
{
	mStatesSystem->addNormalState(xNumber, xState);
}

//-------------------------------------------------------------
// iSystemsListener
//-------------------------------------------------------------
bool MainSystem::frameStarted(const Ogre::FrameEvent& evt)
{
	if(mStateLoad != true)
	{
		mPhysicsSystem->needUpdate(evt);
		mInputSystem->needUpdate();
		mStatesSystem->needUpdate(evt);
	}

	return !mNeedShutdown;
}

bool MainSystem::frameEnded(const Ogre::FrameEvent& evt)
{
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

void MainSystem::stateStartLoad()
{
	mStateLoad = true;
}

void MainSystem::stateEndLoad()
{
	mStateLoad = false;
}

//-------------------------------------------------------------
// iCore
//-------------------------------------------------------------
void MainSystem::needSwitchToStateId(int xStateId, bool xShowLoadState)
{
	mStatesSystem->switchToState(xStateId, xShowLoadState);
}

void MainSystem::stateLoadProgress(int xProgressValue, std::string xText)
{
	mStatesSystem->injectStateLoadProgress(xProgressValue, xText);
	mGraphicSystem->needSingleUpdate();
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