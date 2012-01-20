#pragma once

#include "State.h"

class MainMenuState: public State
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);
};

