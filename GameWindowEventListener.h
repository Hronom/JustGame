#ifndef GAMEWINDOWEVENTLISTENER_H
#define GAMEWINDOWEVENTLISTENER_H


#include <Ogre.h>
#include <OISMouse.h>
#include "iMainListener.h"

class GameWindowEventListener: public Ogre::WindowEventListener
{
private:
	iMainListener *mListener;
	OIS::Mouse* mMouse;

public:
	GameWindowEventListener(iMainListener *xListener, OIS::Mouse* xMouse);

	virtual void windowResized(Ogre::RenderWindow* xRenderWindow);
	virtual void windowClosed(Ogre::RenderWindow* xRenderWindow);
};

#endif

