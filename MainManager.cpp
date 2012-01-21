#include "MainManager.h"

MainManager::MainManager(MyGUI::Gui *xMyGUI, Ogre::SceneManager *xSceneManager)
{
	mNeedShutdown = false;

	mGUIManager = new GUIManager(xMyGUI);
	mObjectsManager = new ObjectsManager();
	mStateManager = new StateManager(this, mGUIManager);
}


MainManager::~MainManager()
{
	delete mStateManager;
	mStateManager = 0;
	delete mObjectsManager;
	mObjectsManager = 0;
	delete mGUIManager;
	mGUIManager = 0;	
}

bool MainManager::needUpdate(const Ogre::FrameEvent& evt)
{
	return !mNeedShutdown;
}

void MainManager::mouseMoved(const OIS::MouseEvent& e)
{
	mGUIManager->mouseMoved(e);
}

void MainManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGUIManager->mousePressed(e, id);
}

void MainManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mGUIManager->mouseReleased(e, id);
}

void MainManager::keyPressed(const OIS::KeyEvent& e)
{
	mGUIManager->keyPressed(e);
}

void MainManager::keyReleased(const OIS::KeyEvent& e)
{
	mGUIManager->keyReleased(e);
}

void  MainManager::needShutdown()
{
	mNeedShutdown = true;
}

