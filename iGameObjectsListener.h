#ifndef IGAMEOBJECTSLISTENER_H
#define IGAMEOBJECTSLISTENER_H

#include <Ogre.h>

class iGameObjectsListener
{
public:
	virtual void addBullet(short xObjectType, Ogre::Vector2 xPos, Ogre::Vector2 xDestination) = 0;

};

#endif