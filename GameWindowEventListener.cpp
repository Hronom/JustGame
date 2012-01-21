#include "GameWindowEventListener.h"

GameWindowEventListener::GameWindowEventListener(iMainListener *xListener, OIS::Mouse* xMouse)
{
	mListener = xListener;

	mMouse = xMouse;
}

void GameWindowEventListener::windowResized(Ogre::RenderWindow* xRenderWindow)
{
	unsigned int xWidth, xHeight, xDepth;
	int xLeft, xTop;
	xRenderWindow->getMetrics(xWidth, xHeight, xDepth, xLeft, xTop);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = xWidth;
	ms.height = xHeight;
}

void GameWindowEventListener::windowClosed(Ogre::RenderWindow* xRenderWindow)
{

}