#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include "iMainListener.h"
#include "GraphicSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"

class MainSystem : public iMainListener
{
private:
	bool mNeedShutdown;

	GraphicSystem *mGraphicSystem;
	PhysicsSystem *mPhysicsSystem;
	InputSystem *mInputSystem;

public:
	MainSystem();
	virtual ~MainSystem();
	bool run();

	virtual bool needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);
};

#endif