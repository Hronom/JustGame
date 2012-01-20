#include "GameKeyListener.h"


GameKeyListener::GameKeyListener(MainListener *xListener)
{
	mListener = xListener;
}

bool GameKeyListener::keyPressed(const OIS::KeyEvent& e)
{ 
	mListener->keyPressed(e);

	return true;
}

bool GameKeyListener::keyReleased(const OIS::KeyEvent& e)
{ 
	mListener->keyReleased(e);

	return true; 
}