#pragma once

#include <Ogre.h>
#include <OISMouse.h>
#include "MainListener.h"

class GameWindowEventListener: public Ogre::WindowEventListener
{
private:
	MainListener *mListener;
	OIS::Mouse* mMouse;

public:
	GameWindowEventListener(MainListener *xListener, OIS::Mouse* xMouse);

	virtual void windowResized(Ogre::RenderWindow* xRenderWindow);
	virtual void windowClosed(Ogre::RenderWindow* xRenderWindow);
};

