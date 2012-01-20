#pragma once

#include "Ogre.h"
#include "OgreFrameListener.h"
#include <OIS/OIS.h>

class MainListener
{
public:
	MainListener();

	virtual void needUpdate(const Ogre::FrameEvent& evt) = 0;
	virtual	void mouseMoved(const OIS::MouseEvent& e) = 0;
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual	void keyPressed(const OIS::KeyEvent& e) = 0;
	virtual void keyReleased(const OIS::KeyEvent& e) = 0;
};

