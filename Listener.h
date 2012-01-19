#ifndef LISTENER_H
#define LISTENER_H

#include <OgreRenderWindow.h>

class Listener
{
public:
	Listener();
	~Listener();

	virtual void update(const Ogre::FrameEvent& xFrameEvent) = 0;
};

#endif

