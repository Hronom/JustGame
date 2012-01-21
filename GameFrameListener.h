#ifndef GAMEFRAMELISTENER_H
#define GAMEFRAMELISTENER_H

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OIS/OIS.h>

#include "iMainListener.h"

class GameFrameListener : public Ogre::FrameListener 
{ 
private: 
	iMainListener *mListener;
	OIS::Keyboard* mKeyboard; 
	OIS::Mouse* mMouse; 

public: 
	GameFrameListener(iMainListener *xListener, OIS::Keyboard* xKeyboard, OIS::Mouse* xMouse);
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
}; 

#endif


