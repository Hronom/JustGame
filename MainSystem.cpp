#include "MainSystem.h"

MainSystem::MainSystem()
{
	mNeedShutdown = false;
}

MainSystem::~MainSystem()
{

}

bool MainSystem::run()
{
	mGraphicSystem = new GraphicSystem(this);
	mGraphicSystem->init();
	mPhysicsSystem = new PhysicsSystem(this);
	mPhysicsSystem->init(mGraphicSystem->getSceneManager());
	mInputSystem = new InputSystem(this);
	mInputSystem->init(mGraphicSystem->getWinHandle(), mGraphicSystem->getWinWidth(), mGraphicSystem->getWinHeight());
	
	mGraphicSystem->start();

	return true;
}

bool MainSystem::needUpdate(const Ogre::FrameEvent& evt)
{
	mInputSystem->needUpdate();

	return !mNeedShutdown;
}

void MainSystem::mouseMoved(const OIS::MouseEvent& e)
{
	mGraphicSystem->injectMouseMoved(e);
}

void MainSystem::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGraphicSystem->injectMousePressed(e, id);
}

void MainSystem::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGraphicSystem->injectMouseReleased(e, id);
}

void MainSystem::keyPressed(const OIS::KeyEvent& e)
{
	mGraphicSystem->injectKeyPressed(e);
}

void MainSystem::keyReleased(const OIS::KeyEvent& e)
{
	mGraphicSystem->injectKeyReleased(e);
}