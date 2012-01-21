#include "GameMouseListener.h"

GameMouseListener::GameMouseListener(iMainListener *xListener)
{
	mListener = xListener;
}

bool GameMouseListener::mouseMoved(const OIS::MouseEvent& e)
{
	mListener->mouseMoved(e);

	return true; 
}

bool GameMouseListener::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{ 
	mListener->mousePressed(e, id);

	return true; 
}

bool GameMouseListener::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{ 
	mListener->mouseReleased(e, id);

	return true; 
}