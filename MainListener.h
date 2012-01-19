#ifndef MAINLISTENER_H
#define MAINLISTENER_H

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class MainListener: public Ogre::WindowEventListener, public Ogre::FrameListener
{
private:
	// OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

public:
	MainListener(OIS::InputManager* xInputManager);
	~MainListener();

	void init();

	// Ogre::WindowEventListener
	virtual void windowResized(Ogre::RenderWindow* xRenderWindow);
	virtual void windowClosed(Ogre::RenderWindow* xRenderWindow);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& xFrameEvent);
};

#endif
