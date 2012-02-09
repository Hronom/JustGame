#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include "iMainListener.h"
#include "GraphicSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "StatesSystem.h"

#include "iState.h"

class MainSystem : public iMainListener, public iCore
{
private:
	bool mNeedShutdown;

	GraphicSystem *mGraphicSystem;
	PhysicsSystem *mPhysicsSystem;
	InputSystem *mInputSystem;
	StatesSystem *mStatesSystem;

public:
	MainSystem();
	virtual ~MainSystem();
	bool init();
	void run();	
	void addState(int xNumber, iState *xState);

	//-------------------------------------------------------------
	// iMainListener
	//-------------------------------------------------------------
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	//-------------------------------------------------------------
	// iCore
	//-------------------------------------------------------------
	virtual void needSwitchToStateId(int xStateId);
	virtual void needShutdown();

	virtual void loadGUILayout(Ogre::String xLayoutName);
	virtual void unloadGUILayout();
	virtual void addButtonDelegate(Ogre::String xButtonName, iState *xState);

	virtual Ogre::SceneManager* getSceneManager();
	virtual Ogre::Camera* getCamera();
	virtual OgreBulletDynamics::DynamicsWorld* getDynamicsWorld();
};

#endif