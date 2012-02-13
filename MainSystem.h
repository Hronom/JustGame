#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include "iSystemsListener.h"
#include "GraphicSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "StatesSystem.h"

#include "iState.h"

class MainSystem : public iSystemsListener, public iCore
{
private:
	GraphicSystem *mGraphicSystem;
	PhysicsSystem *mPhysicsSystem;
	InputSystem *mInputSystem;
	StatesSystem *mStatesSystem;

	bool mNeedShutdown;
	bool mStateLoad;

public:
	MainSystem();
	virtual ~MainSystem();
	bool init();
	void run();

	void setLoadState(iLoadState *xLoadState);
	void addNormalState(int xNumber, iState *xState);

	//-------------------------------------------------------------
	// iSystemsListener
	//-------------------------------------------------------------
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);
	virtual void windowResized(unsigned int xNewWidth, unsigned int xNewHeight);
	virtual void windowClosed();
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	virtual void stateStartLoad();
	virtual void stateEndLoad();

	//-------------------------------------------------------------
	// iCore
	//-------------------------------------------------------------
	virtual void needSwitchToStateId(int xStateId, bool xShowLoadState = false);
	virtual void stateLoadProgress(int xProgressValue, std::string xText);
	virtual void needShutdown();

	virtual Ogre::SceneManager* getSceneManager();
	virtual Ogre::Camera* getCamera();
	virtual	MyGUI::Gui* getGui();
	virtual OgreBulletDynamics::DynamicsWorld* getDynamicsWorld();
};

#endif