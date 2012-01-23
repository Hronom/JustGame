#ifndef BULLET_H
#define BULLET_H

#include <Ogre.h>

#include "iCore.h"
#include "GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet(iCore *xCore, Ogre::String xObjectName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);
	~Bullet();

	virtual void update(const Ogre::FrameEvent& evt);
};

#endif

