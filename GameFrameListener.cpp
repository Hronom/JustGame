#include "GameFrameListener.h"

GameFrameListener::GameFrameListener(iMainListener *xListener, OIS::Keyboard* xKeyboard, OIS::Mouse* xMouse) 
{ 
	mListener = xListener;

	mKeyboard = xKeyboard; 
	mMouse = xMouse; 
} 

bool GameFrameListener::frameStarted(const  Ogre::FrameEvent& evt) 
{
	mKeyboard->capture();
	mMouse->capture();

	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)) 
		return false; 

	return mListener->needUpdate(evt);
}

bool GameFrameListener::frameEnded(const  Ogre::FrameEvent& evt) 
{ 
	return true; 
}