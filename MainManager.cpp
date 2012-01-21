#include "MainManager.h"

MainManager::MainManager(MyGUI::Gui *xMyGUI, Ogre::SceneManager *xSceneManager)
{
	mNeedShutdown = false;

	mGUIManager = new GUIManager(xMyGUI);
	mObjectsManager = new ObjectsManager(this, xSceneManager);
	mStateManager = new StateManager(this);
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
	mStateManager->needUpdate(evt);
	mObjectsManager->needUpdate(evt);
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

void MainManager::loadGUILayout(std::string xLayoutName)
{
	mGUIManager->loadLayout(xLayoutName);
}

void MainManager::unloadGUILayout()
{
	mGUIManager->unloadLayout();
}

void MainManager::addButtonDelegate(std::string xButtonName, iState *xState)
{
	mGUIManager->addButtonDelegate(xButtonName, xState);
}

void MainManager::addPlayer(Ogre::Vector3 xPos)
{
	mObjectsManager->addPlayer(xPos);
}

void MainManager::addEnemy(Ogre::Vector3 xPos)
{
}

void MainManager::movePlayerUp()
{
	mObjectsManager->movePlayerUp();
}

void MainManager::movePlayerDown()
{
	mObjectsManager->movePlayerDown();
}

void MainManager::movePlayerLeft()
{
	mObjectsManager->movePlayerLeft();
}

void MainManager::movePlayerRight()
{
	mObjectsManager->movePlayerRight();
}

void MainManager::playerShoot()
{
	mObjectsManager->playerShoot();
}

