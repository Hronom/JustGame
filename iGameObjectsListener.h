#ifndef IGAMEOBJECTSLISTENER_H
#define IGAMEOBJECTSLISTENER_H

#include <Ogre.h>

class iGameObjectsListener
{
public:
	virtual void addBullet(Ogre::String xObjectString, Ogre::Vector2 xPos, Ogre::Vector2 xDestination) = 0;

};

#endif