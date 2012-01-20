#pragma once

#include <OgreFrameListener.h>
#include <OIS/OIS.h>

class State
{
public:
	State();
	virtual ~State();

	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void needUpdate(const Ogre::FrameEvent& evt) = 0;
	virtual	void mouseMoved(const OIS::MouseEvent& e) = 0;
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual	void keyPressed(const OIS::KeyEvent& e) = 0;
	virtual void keyReleased(const OIS::KeyEvent& e) = 0;
};

