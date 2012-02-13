#include "StatesSystem.h"

StatesSystem::StatesSystem(iSystemsListener *xMainListener)
{
	mMainListener = xMainListener;

	mLoadState = 0;
	mCurrentState = 0;
}

StatesSystem::~StatesSystem()
{
	if(mLoadState != 0)
	{
		delete mLoadState;
		mLoadState = 0;
	}

	for(unsigned i=0; i < mStatesMap.size(); i++)
	{
		//mStatesMap[i]->exit();
		delete mStatesMap[i];
	}

	mStatesMap.clear();
}

bool StatesSystem::init()
{
	return true;
}

void StatesSystem::needUpdate(const Ogre::FrameEvent& evt)
{
	if(mCurrentState != 0) mCurrentState->needUpdate(evt);
}

void StatesSystem::injectMouseMoved(const OIS::MouseEvent& e)
{
	if(mCurrentState != 0) mCurrentState->mouseMoved(e);
}

void StatesSystem::injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(mCurrentState != 0) mCurrentState->mousePressed(e, id);
}

void StatesSystem::injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(mCurrentState != 0) mCurrentState->mouseReleased(e, id);
}

void StatesSystem::injectKeyPressed(const OIS::KeyEvent& e)
{
	if(mCurrentState != 0) mCurrentState->keyPressed(e);
}

void StatesSystem::injectKeyReleased(const OIS::KeyEvent& e)
{
	if(mCurrentState != 0) mCurrentState->keyReleased(e);
}

void StatesSystem::injectStateLoadProgress(int xProgressValue, std::string xText)
{
	if(mLoadState != 0) mLoadState->setProgress(xProgressValue, xText);
}

void StatesSystem::setLoadState(iLoadState *xLoadState)
{
	mLoadState = xLoadState;
}

void StatesSystem::addNormalState(int xNumber, iState *xState)
{
	mStatesMap[xNumber] = xState;
}

void StatesSystem::switchToState(int xStateId, bool xShowLoadState)
{
	if(mStatesMap.count(xStateId) > 0)
	{
		if(mCurrentState != 0)
		{
			mCurrentState->exit();
			mCurrentState = 0;
		}

		if(xShowLoadState == true)
		{
			mMainListener->stateStartLoad();
			mLoadState->show();
			mStatesMap[xStateId]->prepareState();
			mLoadState->hide();
			mMainListener->stateEndLoad();

			mCurrentState = mStatesMap[xStateId];
			mCurrentState->enter();
		}
		else
		{
			mCurrentState = mStatesMap[xStateId];
			mCurrentState->prepareState();
			mCurrentState->enter();
		}
	}
}
