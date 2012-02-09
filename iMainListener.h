#ifndef IMAINLISTENER_H
#define IMAINLISTENER_H

#include "Ogre.h"
#include "OgreFrameListener.h"
#include <OIS/OIS.h>

class iMainListener
{
public:
	iMainListener() {};
	virtual ~iMainListener() {};

	virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
	virtual	void mouseMoved(const OIS::MouseEvent& e) = 0;
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
	virtual	void keyPressed(const OIS::KeyEvent& e) = 0;
	virtual void keyReleased(const OIS::KeyEvent& e) = 0;
	//virtual void GUIButtonClicked(MyGUI::WidgetPtr xSender) = 0;
};

#endif
