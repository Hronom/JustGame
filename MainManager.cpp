#include "MainManager.h"

MainManager::MainManager(MyGUI::Gui *xMyGUI, Ogre::SceneManager *xSceneManager, Ogre::Camera* xCamera)
{
	mNeedShutdown = false;

	mSceneManager = xSceneManager;
	mCamera = xCamera;

	mGUIManager = new GUIManager(xMyGUI);
	mStateManager = new StateManager(this);
}


MainManager::~MainManager()
{
	delete mStateManager;
	mStateManager = 0;
	delete mGUIManager;
	mGUIManager = 0;
}

bool MainManager::needUpdate(const Ogre::FrameEvent& evt)
{
	mStateManager->needUpdate(evt);
	return !mNeedShutdown;
}

void MainManager::mouseMoved(const OIS::MouseEvent& e)
{
	mStateManager->mouseMoved(e);
	mGUIManager->mouseMoved(e);
}

void MainManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mStateManager->mousePressed(e, id);
	mGUIManager->mousePressed(e, id);
}

void MainManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mStateManager->mouseReleased(e, id);
	mGUIManager->mouseReleased(e, id);
}

void MainManager::keyPressed(const OIS::KeyEvent& e)
{
	mStateManager->keyPressed(e);
	mGUIManager->keyPressed(e);
}

void MainManager::keyReleased(const OIS::KeyEvent& e)
{
	mStateManager->keyReleased(e);
	mGUIManager->keyReleased(e);
}

//-------------------------------------------------------------
// iCore
//-------------------------------------------------------------
void MainManager::needSwitchToStateId(int xStateId)
{
	mStateManager->switchToStateId(xStateId);
}

void MainManager::needShutdown()
{
	mNeedShutdown = true;
}

void MainManager::loadGUILayout(Ogre::String xLayoutName)
{
	mGUIManager->loadLayout(xLayoutName);
}

void MainManager::unloadGUILayout()
{
	mGUIManager->unloadLayout();
}

void MainManager::addButtonDelegate(Ogre::String xButtonName, iState *xState)
{
	mGUIManager->addButtonDelegate(xButtonName, xState);
}

Ogre::SceneManager* MainManager::getSceneManager()
{
	return mSceneManager;
}

Ogre::Camera* MainManager::getCamera()
{
	return mCamera;
}