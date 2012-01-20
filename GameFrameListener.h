#pragma once

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OIS/OIS.h>

#include "MainListener.h"

class GameFrameListener : public Ogre::FrameListener 
{ 
private: 
	MainListener *mListener;
	OIS::Keyboard* mKeyboard; 
	OIS::Mouse* mMouse; 

public: 
	GameFrameListener(MainListener *xListener, OIS::Keyboard* xKeyboard, OIS::Mouse* xMouse);
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
}; 


