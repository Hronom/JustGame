#include "StateManager.h"

#include "MainMenuState.h"
#include "PlayGameState.h"


StateManager::StateManager(iCore *xCore)
{
	mStatesMap[0] = new MainMenuState(xCore);
	mStatesMap[1] = new PlayGameState(xCore);

	mCurrentState = mStatesMap[0];

	mCurrentState->enter();
}


StateManager::~StateManager()
{
	for(int i=0; i < mStatesMap.size(); i++)
	{
		mStatesMap[i]->exit();

		delete mStatesMap[i];
	}

	mStatesMap.clear();
}

void StateManager::needUpdate(const Ogre::FrameEvent& evt)
{
	mCurrentState->needUpdate(evt);
}

void StateManager::mouseMoved(const OIS::MouseEvent& e)
{
	mCurrentState->mouseMoved(e);
}

void StateManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mCurrentState->mousePressed(e, id);
}

void StateManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	mCurrentState->mouseReleased(e, id);
}

void StateManager::keyPressed(const OIS::KeyEvent& e)
{
	mCurrentState->keyPressed(e);
}

void StateManager::keyReleased(const OIS::KeyEvent& e)
{
	mCurrentState->keyReleased(e);
}

void StateManager::switchToStateId(int xStateId)
{
	mCurrentState->exit();
	mCurrentState = mStatesMap[xStateId];
	mCurrentState->enter();
}