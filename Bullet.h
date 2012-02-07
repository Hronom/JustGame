#ifndef BULLET_H
#define BULLET_H

#include <Ogre.h>

#include "iCore.h"
#include "GameObject.h"

class Bullet: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;

	Ogre::Real mLiveTime;
	Ogre::Real mTimeBeforeDelete;

public:
	Bullet(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);
	~Bullet();

	virtual void update(const Ogre::FrameEvent& evt);
	virtual int getDamage();
};

#endif

